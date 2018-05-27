//
// Created by joren on 21/04/2018.
//

#include "../headers/2DLineDrawings.h"

LineDrawing2D::LineDrawing2D(const ImageInfo *imgInfo) {
    info = imgInfo;
}

img::EasyImage LineDrawing2D::LinesToImage(const LinesList2D &lines) {

    // Variables
    double x_min, x_max, y_min, y_max,
            x_range, y_range;

    // Iterate over all 2DLines.
    bool firstItr = true;
    for (LinesList2D::const_iterator itr = lines.begin(); itr != lines.end(); itr++) {
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

    // Add padding if it's a single horizontal/vertical line.
    if (image_x == 0) {
        image_x += 3;
    }
    if (image_y == 0) {
        image_y += 3;
    }

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

    // Setup image with correct dimensions and set correct background color.
    img::EasyImage image(image_x, image_y);
    image.clear(background);

    // Iterate over all lines
    for (LinesList2D::const_iterator itr = lines.begin(); itr != lines.end(); ++itr) {
        Line2D *curLine = *itr;

        // Draw line.
        img::Color color((uint8_t) curLine->color->r,
                         (uint8_t) curLine->color->g,
                         (uint8_t) curLine->color->b);
        image.draw_line(curLine->start->x, curLine->start->y, curLine->end->x, curLine->end->y, color);
    }

    // Return resulting image.
    return image;
}

const ImageInfo *LineDrawing2D::getInfo() const {
    return info;
}