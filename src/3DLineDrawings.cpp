//
// Created by joren on 5/05/2018.
//

#include "../headers/3DLineDrawings.h"

LineDrawing3D::LineDrawing3D(const ImageInfo *imgInfo) {
    info = imgInfo;
}

void LineDrawing3D::PointsToECS(int figure_id) {

    // Get required stuff from info.
    Point3D *eye = info->getEye();

    // setup eye vector and calculate angles
    Vector3D eyeVec = Vector3D::point(eye->x, eye->y, eye->z);
    double r = eyeVec.length();
    double angleRZ = acos(eyeVec.z / r);
    double angleRX = asin((eyeVec.y / (r * sin(angleRZ))));

    // Iterate over all points
    LD3D_Properties *prop = getInfo()->getLD3DProperties().at(figure_id);
    for (vector<Point3D*>::iterator itr = prop->points.begin(); itr != prop->points.end(); ++itr) {
        Point3D *curPoint = *itr;

        cout << "\nPointsToECS: " << endl;
        cout << "( " << curPoint->x << ", " << curPoint->y << ", " << curPoint->z << ")";


        // Rotate around Z-axis so X-axis points right
        // M_PI_2 = PI / 2
        double angle = angleRX + M_PI_2;

        // Create vector.
        Vector3D vec = Vector3D::point(curPoint->x, curPoint->y, curPoint->z);

        Matrix Mz;
        Mz(1, 1) = cos(angle);
        Mz(1, 2) = -sin(angle);
        Mz(2, 1) = sin(angle);
        Mz(2, 2) = cos(angle);

        //Multiply
        vec *= Mz;

        // Rotate around x-axis
        Matrix Mx;
        Mx(2, 2) = cos(angleRZ);
        Mx(2, 3) = -sin(angleRZ);
        Mx(3, 2) = sin(angleRZ);
        Mx(3, 3) = cos(angleRZ);

        //Multiply
        vec *= Mx;

        // Translation to move origin
        Matrix M;
        M(4, 3) = -r;

        // Multiply
        vec *= M;

        // Set new values
        curPoint->x = vec.x;
        curPoint->y = vec.y;
        curPoint->z = vec.z;


        cout << " -> ( " << curPoint->x << ", " << curPoint->y << ", " << curPoint->z << ")" << endl;
    }
}

vector<Point2D*> LineDrawing3D::PerspectiveProjection(int figure_id) {

    // Iterate over all points
    LD3D_Properties *prop = getInfo()->getLD3DProperties().at(figure_id);
    for (vector<Point3D*>::iterator itr = prop->points.begin(); itr != prop->points.end(); ++itr) {
        Point3D *curPoint = *itr;

        cout << "\nPerspectiveProjection Points: " << endl;
        cout << "( " << curPoint->x << ", " << curPoint->y << ", " << curPoint->z << ")" << endl;

        // Distance d = 1
        double d  = 1;

        // Calculate x = x', y = y' and z = -d
        curPoint->x = -((d * curPoint->x) / curPoint->z);
        curPoint->y = -((d * curPoint->y) / curPoint->z);
        curPoint->z = -d;

        cout << "\nPerspectiveProjection Points After: " << endl;
        cout << "( " << curPoint->x << ", " << curPoint->y << ", " << curPoint->z << ")" << endl;
    }
}

tuple<uint, uint> LineDrawing3D::CalculateImageProperties(int figure_id) {

    LD3D_Properties *prop = getInfo()->getLD3DProperties().at(figure_id);

    // z coordinates can be ignored since it's a 2D projection.
    // Variables
    double x_min, x_max, y_min, y_max,
            x_range, y_range;

    // Iterate over all 2DLines.
    bool firstItr = true;
    std::vector<Line3D*>::const_iterator itr;
    for (itr = prop->lines.begin(); itr != prop->lines.end(); itr++) {
        Line3D *cur_line = (*itr);
        Point3D *start = cur_line->start;
        Point3D *end = cur_line->end;

        cout << "\nCalculateImageProperties Drawing: " << endl;
        cout << "( " << cur_line->start->x << ", " << cur_line->start->y << ", " << cur_line->start->z << ") -> ( " << cur_line->end->x << ", " << cur_line->end->y << ", " << cur_line->end->z << ")" << endl;


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

    cout << "XMAX : " << x_max << endl;
    cout << "XMIN : " << x_min << endl;
    cout << "YMAX : " << y_max << endl;
    cout << "YMIN : " << y_min << endl;

    // Calculate x_range and y_range.
    x_range = x_max - x_min;
    y_range = y_max - y_min;
    cout << "XRANGE : " << x_range << endl;
    cout << "YRANGE : " << x_range << endl;

    // Calculate image size (when scaled).
    uint image_x = getInfo()->getSize() * (x_range / __max(x_range, y_range));
    uint image_y = getInfo()->getSize() * (y_range / __max(x_range, y_range));

    cout << "IMAGEX : " << image_x << endl;
    cout << "IMAGEY : " << image_y << endl;


    // Scaling factor (d)
    double d = 0.95 * (image_x / x_range);


    cout << "D : " << d << endl;

    // multiply coordinates of all points with d
    for (vector<Line3D*>::const_iterator itr = prop->lines.begin(); itr != prop->lines.end(); ++itr) {
        Line3D *curLine = *itr;
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

    return make_tuple(image_x, image_y);

    // Add (dx, dy) to all coordinates and round
    for (vector<Line3D*>::const_iterator itr = prop->lines.begin(); itr != prop->lines.end(); ++itr) {
        Line3D *curLine = *itr;
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

    return make_tuple(image_x, image_y);
}

img::EasyImage LineDrawing3D::LinesToImage(int figure_id) {

    LD3D_Properties *prop = getInfo()->getLD3DProperties().at(figure_id);

    tuple<uint, uint> size = CalculateImageProperties(figure_id);

    // Setup image with correct dimensions
    img::EasyImage image(get<0>(size), get<1>(size));

    // Set correct background color.
    img::Color background((uint8_t)(getInfo()->getBGColor()->r),
                          (uint8_t)(getInfo()->getBGColor()->g),
                          (uint8_t)(getInfo()->getBGColor()->b));
    image.clear(background);

    // Setup draw color
    img::Color color((uint8_t)(prop->color->r),
                     (uint8_t)(prop->color->g),
                     (uint8_t)(prop->color->b));

    // Iterate over all lines
    for (vector<Line3D*>::iterator itr = prop->lines.begin(); itr != prop->lines.end(); ++itr) {
        Line3D *curLine = *itr;

        cout << "\nLinesToImage Drawing: " << endl;
        cout << "( " << curLine->start->x << ", " << curLine->start->y << ", " << curLine->start->z << ") -> ( " << curLine->end->x << ", " << curLine->end->y << ", " << curLine->end->z << ")" << endl;
        // Draw line
        image.draw_line(round(curLine->start->x), round(curLine->start->y), round(curLine->end->x), round(curLine->end->y), color);

    }
    return image;
}

img::EasyImage LineDrawing3D::GenerateImage(int figure_id) {

    PointsToECS(figure_id);
    PerspectiveProjection(figure_id);
    return LinesToImage();
}

const ImageInfo *LineDrawing3D::getInfo() const {
    return info;
}