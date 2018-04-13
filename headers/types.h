//
// Created by joren on 13/04/2018.
//

#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

// Colors.

class ColorRGB {
public:
    double r, g, b;
};

class ColorRGBA {
public:
    double r, g, b, a;
};


// Points.

class Point2D {
public:
    double x, y;
};

class Point3D {
public:
    double x, y, z;
};


// Lines

class Line2D {
public:
    Point2D *start;
    Point2D *end;
    ColorRGB *color;
};

class Line3D {
public:
    Point3D *start;
    Point3D *end;
    ColorRGB *color;
};


#endif //ENGINE_TYPES_H
