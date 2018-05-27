//
// Created by joren on 13/04/2018.
//

#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

#include "../vector3d/vector3d.h"
#include "list"
#include "string"
#include "vector"


class ColorRGB {
public:
    double r, g, b;

    ColorRGB() {
        r = 0;
        g = 0;
        b = 0;
    }
    ColorRGB(double _r, double _g, double _b) {
        r = _r;
        g = _g;
        b = _b;
    }
};

// 2D
class Point2D {
public:
    double x, y;

    Point2D(double _x, double _y) {
        x = _x;
        y = _y;
    }
};

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

struct LS2D_Properties {
    std::string pathToFile;
    ColorRGB *color;
};


// 3D

class Line3D {
public:
    Vector3D start;
    Vector3D end;
    ColorRGB *color;

    Line3D(const double x_start, const double y_start, const double z_start, const double x_end, const double y_end, const double z_end) {
        start = Vector3D::point(x_start, y_start, z_start);
        end = Vector3D::point(x_end, y_end, z_end);
        ColorRGB(255, 255, 255);
    }

    Line3D(Vector3D _start, Vector3D _end) {
        start = _start;
        end = _end;
        ColorRGB(255, 255, 255);
    }
};

class Face {
public:
    std::vector<int> point_indices;
};

class Figure {
public:
    std::string type;
    double scale;
    double rotateX;
    double rotateY;
    double rotateZ;
    Vector3D center;
    int nrPoints;
    int nrLines;
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    ColorRGB color;

};

class LD3D_Properties {
public:
    Vector3D eye;
    int nrFigures;
    std::vector<Figure> Figures;
};

// typedefs

typedef unsigned int uint;
typedef std::vector<Line2D*> LinesList2D;
typedef std::vector<Figure> FiguresList3D;


#endif //ENGINE_TYPES_H
