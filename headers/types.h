//
// Created by joren on 13/04/2018.
//

#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

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




#endif //ENGINE_TYPES_H
