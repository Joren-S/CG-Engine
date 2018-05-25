//
// Created by joren on 13/04/2018.
//

#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

#include "list"


// Colors.

class ColorRGB {
public:
    double r, g, b;

    ColorRGB(double _r, double _g, double _b) {
        r = _r;
        g = _g;
        b = _b;
    }
};

class ColorRGBA {
public:
    double r, g, b, a;

    ColorRGBA(double _r, double _g, double _b, double _a) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }
};


// Points.

class Point2D {
public:
    double x, y;

    Point2D(double _x, double _y) {
        x = _x;
        y = _y;
    }
};

class Point3D {
public:
    double x, y, z;

    Point3D(double _x, double _y, double _z) {
        x = _x;
        y = _y;
        z = _z;
    }
};


// Lines

class Line2D {
public:
    Point2D *start;
    Point2D *end;
    ColorRGB *color;

    Line2D(double x_start, double y_start, double x_end, double y_end) {
        start = new Point2D(x_start, y_start);
        end = new Point2D(x_end, y_end);
        ColorRGB(255, 255, 255);
    }

    Line2D(Point2D *_start, Point2D *_end) {
        start = _start;
        end = _end;
        ColorRGB(255, 255, 255);
    }
};

class Line3D {
public:
    Point3D *start;
    Point3D *end;
    ColorRGB *color;

    Line3D(double x_start, double y_start, double z_start, double x_end, double y_end, double z_end) {
        start = new Point3D(x_start, y_start, z_start);
        end = new Point3D(x_end, y_end, z_end);
        ColorRGB(255, 255, 255);
    }

    Line3D(Point3D *_start, Point3D *_end) {
        start = _start;
        end = _end;
        ColorRGB(255, 255, 255);
    }
};

// typedefs

typedef unsigned int uint;
typedef std::list<Line2D*> LinesList2D;
typedef std::list<Line3D*> LinesList3D;


#endif //ENGINE_TYPES_H
