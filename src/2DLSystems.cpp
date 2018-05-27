//
// Created by joren on 21/04/2018.
//

#include "../headers/2DLSystems.h"

using namespace std;

// Primary functions

LSystem2D::LSystem2D(const ImageInfo *imgInfo) {
    // Setup variables.
    filebuf buffer;
    stringstream path;
    path << "../examples/ls2d/" << imgInfo->getLS2DProperties()->pathToFile;

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
                Line2D *newline = new Line2D(curLocation.x, curLocation.y, nextLocation.x, nextLocation.y);
                newline->color = getInfo()->getLS2DProperties()->color;
                result.push_back(newline);
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

img::EasyImage LSystem2D::GenerateImage() {
    // Process system
    LinesList2D Lines = ProcessLSystem();

    // Convert to EasyImage and return
    LineDrawing2D drawing(getInfo());
    return drawing.LinesToImage(Lines);
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

                // Decide if something is drawn based on probability
                /*
                 rand() return value in range [0, RAND_MAX].
                 Divide this value by RAND_MAX for a random number between 0 and 1.
                 Next, check if lower than our given probability.

                 we want 0 to always return false:
                 <p and not <=p
                 we want 1.0 to always return true:
                 divide by RAND_MAX / 1 instead of just RAND_MAX.
                 */
                bool doDraw = rand() / (RAND_MAX + 1.0) < lsys->get_probability(curChar);

                // append replacement if needed
                if (doDraw) {
                    buf << lsys->get_replacement(curChar);
                }
                else {
                    buf << curChar;
                }
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