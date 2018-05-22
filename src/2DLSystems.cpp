//
// Created by joren on 1/04/2018.
//

#include "../headers/2DLSystems.h"

using namespace std;

// Primary functions

LSystem2D::LSystem2D(const string &pathToL2D, const ImageInfo *imgInfo) {
    // Setup variables.
    filebuf buffer;
    stringstream path;
    path << "../examples/ls2d/" << pathToL2D;

    // Default values are NULL.
    info = NULL;
    ls2d = NULL;

    // If file exists
    if (buffer.open(path.str(), ios::in)) {

        // Parse and set fields.
        istream l2d (&buffer);
        ls2d = new LParser::LSystem2D (l2d);
        info = imgInfo;
    }
}

LinesList2D LSystem2D::ProcessLSystem() {
    // Variables
    LinesList2D result;
    const LParser::LSystem2D *l_system = getLSystem();

    // Build rule and setup starting values for vars.
    string fullRule = buildRule();
    Point2D curLocation = Point2D(0, 0);
    double curAngle = l_system->get_starting_angle();

    // Stack to keep track of branches (brackets).
    stack <tuple<Point2D, double>> branches;

    // Iterate over all characters in rule
    for (string::iterator itr = fullRule.begin(); itr != fullRule.end(); ++itr) {
        char curChar = *itr;

        if (curChar == '(') {
            // Store current branch, since we begin a new one.
            auto branch = make_tuple(curLocation, curAngle);
            branches.push(branch);
        }
        else if (curChar == ')') {
            // If we are in the main branch
            if (branches.empty()) {
                // There is a ')' without '(', so return an empty list.
                return LinesList2D();
            }

            // If not
            else {
                // Close branch and restore to previous branch.
                tuple<Point2D, double> prevBranch = branches.top();
                branches.pop();
                curLocation = get<0>(prevBranch);
                curAngle = get<1>(prevBranch);
            }
        }
        else if (curChar == '+') {
            // Increase angle
            curAngle += l_system->get_angle();
        }
        else if (curChar == '-') {
            // Decrease angle
            curAngle -= l_system->get_angle();
        }
        else {
            // If we have to go forward
            if (l_system->draw(curChar)) {
                // We check for illegal characters in BuildRule, so we can continue and find the next point
                Point2D nextLocation = FindNextPoint(curLocation, curAngle, 1);
                result.push_back(new Line2D(curLocation.x, curLocation.y, nextLocation.x, nextLocation.y));
                curLocation = nextLocation;
            }
        }
    }

    // There is a '(' without ')', so return an empty list.
    if (!branches.empty()) {
        return LinesList2D();
    }

    // Return result.
    return result;
}

img::EasyImage LSystem2D::LinesToImage(const LinesList2D &lines) {

    // Variables
    double x_min, x_max, y_min, y_max,
            x_range, y_range;

    // Iterate over all 2DLines.
    bool firstItr = true;
    std::list<Line2D*>::const_iterator itr;
    for (itr = lines.begin(); itr != lines.end(); itr++) {
        Line2D *cur_line = (*itr);
        Point2D *start = cur_line->start;
        Point2D *end = cur_line->end;

        // Calculate requirements for x-range and y-range.
        if (firstItr) {
            x_min = start->x < end->x ? start->x : end->x;
            y_min = start->y < end->y ? start->y : end->y;
            x_max = start->x > end->x ? start->x : end->x;
            y_max = start->y > end->y ? start->y : end->y;
            firstItr = false;
        }
        else {
            // x_min
            if (start->x < x_min || end->x < x_min) {
                x_min = end->x;
                if (start->x < end->x) {
                    x_min = start->x;
                }
            }
            // y_min
            if (start->y < y_min || end->y < y_min) {
                y_min = end->y;
                if (start->y < end->y) {
                    y_min = start->y;
                }
            }
            // x_max
            if (start->x > x_max || end->x > x_max) {
                x_max = end->x;
                if (start->x > end->x) {
                    x_max = start->x;
                }
            }
            // y_max
            if (start->y > y_max || end->y > y_max) {
                y_max = end->y;
                if (start->y > end->y) {
                    y_max = start->y;
                }
            }
        }
    }

    // Calculate x_range and y_range.
    x_range = x_max - x_min;
    y_range = y_max - y_min;

    // Calculate image size (when scaled).
    unsigned int image_x = getInfo()->getSize() * (x_range / __max(x_range, y_range));
    unsigned int image_y = getInfo()->getSize() * (y_range / __max(x_range, y_range));

    // Scaling factor (d)
    double d = 0.95 * (image_x / x_range);

    // multiply coordinates of all points with d
    for (LinesList2D::const_iterator itr = lines.begin(); itr != lines.end(); ++itr) {
        Line2D *curLine = *itr;
        curLine->start->x *= d;
        curLine->start->y *= d;
        curLine->end->x *= d;
        curLine->end->y *= d;
    }

    // Calculate center point (when scaled).
    int DC_x = d * ((x_min + x_max) / 2);
    int DC_y = d * ((y_min + y_max) / 2);

    // Calculate offset on x and y.
    int dx = (image_x / 2) - DC_x;
    int dy = (image_y / 2) - DC_y;

    // Add (dx, dy) to all coordinates and round
    for (LinesList2D::const_iterator itr = lines.begin(); itr != lines.end(); ++itr) {
        Line2D *curLine = *itr;
        // add
        curLine->start->x += dx;
        curLine->start->y += dy;
        curLine->end->x += dx;
        curLine->end->y += dy;

        // round
        curLine->start->x = round(curLine->start->x);
        curLine->start->y = round(curLine->start->y);
        curLine->end->x = round(curLine->end->x);
        curLine->end->y = round(curLine->end->y);
    }

    // Setup background color
    img::Color background((uint8_t)(getInfo()->getBGColor()->r),
                       (uint8_t)(getInfo()->getBGColor()->g),
                       (uint8_t)(getInfo()->getBGColor()->b));

    // Setup draw color
    img::Color color((uint8_t)(getInfo()->getLS2DProperties()->color->r),
                     (uint8_t)(getInfo()->getLS2DProperties()->color->g),
                     (uint8_t)(getInfo()->getLS2DProperties()->color->b));

    // Setup image with correct dimensions and set correct background color.
    img::EasyImage image(image_x, image_y);
    image.clear(background);

    // Iterate over all lines
    for (LinesList2D::const_iterator itr = lines.begin(); itr != lines.end(); ++itr) {
        Line2D *curLine = *itr;

        // Draw line.
        image.draw_line(curLine->start->x, curLine->start->y, curLine->end->x, curLine->end->y, color);
    }

    // Return resulting image.
    return image;
}

img::EasyImage LSystem2D::GenerateImage() {
    // Process system
    LinesList2D Lines = ProcessLSystem();

    // Return conversion
    return LinesToImage(Lines);
}

// Secondary/helper functions

const bool LSystem2D::isInAlphabet(char _char) {
    // - and + always return false.
    if (_char == '-' or _char == '+') {
        return false;
    }
    // check if char is in alphabet (set).
    return getLSystem()->get_alphabet().find(_char) != getLSystem()->get_alphabet().end();
}

string LSystem2D::buildRule(string curRule, int curIteration) {

    const LParser::LSystem2D *lsys = getLSystem();

    // If no iterations
    if (lsys->get_nr_iterations() == 0) {
        return lsys->get_initiator();
    }

    // If done iterating, return result.
    if (curIteration == lsys->get_nr_iterations()) {
        return curRule;
    }
    // If first iteration, current rule is initatior rule.
    if (curRule.empty()) {
        curRule = lsys->get_initiator();
    }

    // iterate over the current rule and replace all characters from the alphabet.
    stringstream buf;
    for (string::iterator itr = curRule.begin(); itr != curRule.end(); ++itr) {
        char curChar = *itr;

        // if current char is a valid rule
        if (curChar != '+' and curChar != '-' and curChar != '(' and curChar != ')') {
            // if char in alphabet
            if (isInAlphabet(curChar)) {
                // append replacement
                buf << lsys->get_replacement(curChar);
            }
                // if not in alphabet, return empty string.
            else {
                return string();
            }
        }
            // - and + get appended.
        else {
            buf << curChar;
        }
    }

    // recursion for next iteration.
    return buildRule(buf.str(), curIteration + 1);
}

Point2D LSystem2D::FindNextPoint(Point2D start, double angle, uint length) {
    // Convert to radians
    angle = angle * (M_PI / 180);

    // Simple trigonometry
    double dx = length * cos(angle);
    double dy = length * sin(angle);

    // Return as Point2D object.
    return Point2D(start.x + dx, start.y + dy);
}


// Getters
const LParser::LSystem2D *LSystem2D::getLSystem() const {
    return ls2d;
}

const ImageInfo *LSystem2D::getInfo() const {
    return info;
}