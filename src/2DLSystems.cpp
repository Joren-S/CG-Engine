//
// Created by joren on 1/04/2018.
//
#include "../headers/2DLSystems.h"


img::EasyImage DrawLines(const Lines2D &lines, const int size) {

    // Variables
    int x_min = INT32_MAX,
        x_max = INT32_MAX,
        y_min = INT32_MAX,
        y_max = INT32_MAX,
        x_range = INT32_MAX,
        y_range = INT32_MAX;

    // Iterate over all 2DLines.
    std::list<Line2D*>::const_iterator itr;
    for (itr = lines.begin(); itr != lines.end(); itr++) {
        Line2D *cur_line = (*itr);
        Point2D *start = cur_line->start;
        Point2D *end = cur_line->end;

        // Calculate requirements for x-range and y-range.
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

    // Calculate x_range and y_range. (one will always be 1)
    x_range = x_max - x_min;
    y_range = y_max - y_min;

    // Calculate image size (when scaled).
    unsigned int image_x = size * (x_range / __max(x_range, y_range));
    unsigned int image_y = size * (y_range / __max(x_range, y_range));

    // Scaling factor (d)
    int d = 0.95 * (image_x / x_range);

    // Calculate center point (when scaled).
    int DC_x = d * ((x_min + x_max) / 2);
    int DC_y = d * ((y_min + y_max) / 2);

    // Calculate offset on x and y.
    int dx = (image_x / 2) - DC_x;
    int dy = (image_y / 2) - DC_y;

    // Add dx and dy to all coordinates.
}
//std::list<Line2D>