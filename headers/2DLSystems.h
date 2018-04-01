//
// Created by joren on 1/04/2018.
//

#ifndef ENGINE_2DLSYSTEMS_H
#define ENGINE_2DLSYSTEMS_H

#include <list>
#include "../easy_image/easy_image.h"


class ColorRGB {
public:
    double r, g, b;
};

class ColorRGBA {
public:
    double r, g, b, a;
};

class Point2D {
public:
    double x, y;
};

class Line2D {
public:
    Point2D *start;
    Point2D *end;
    ColorRGB *color;
};

typedef std::list<Line2D*> Lines2D;

img::EasyImage DrawLines(const Lines2D &lines, const int size);

#endif //ENGINE_2DLSYSTEMS_H
