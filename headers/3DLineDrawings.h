//
// Created by joren on 5/05/2018.
//

#ifndef ENGINE_3DLINEDRAWINGS_H
#define ENGINE_3DLINEDRAWINGS_H

// standard
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <stack>
#include <cmath>
#include <list>

// provided
#include "../easy_image/easy_image.h"
#include "../l_parser/l_parser.h"
#include "../vector3d/vector3d.h"

// authored
#include "types.h"
#include "input.h"
#include "2DLineDrawings.h"

class LineDrawing3D {
private:
    /**
     * ImageInfo object containing all information from input file.
     */
    const ImageInfo *info;

public:

    /**
     * Constructor.
     * @param imgInfo : ImageInfo object containing specifications for the LSystem.
     */
    LineDrawing3D(const ImageInfo *imgInfo);

    /**
     * Create a matrix for scaling figures.
     * @param scale : scale factor
     * @return : new matrix
     */
    Matrix scaleFigure(const double scale);

    /**
     * Create a matrix for rotating around the X-axis.
     * @param angle : rotation angle
     * @return : new matrix
     */
    Matrix rotateX(const double angle);

    /**
     * Create a matrix for rotating around the Y-axis.
     * @param angle : rotation angle
     * @return : new matrix
     */
    Matrix rotateY(const double angle);

    /**
     * Create a matrix for rotating around the Z-axis.
     * @param angle : rotation angle
     * @return : new matrix
     */
    Matrix rotateZ(const double angle);

    /**
     * Create a matrix for translating figures.
     * @param vec : vector that describes the translation
     * @return : new matrix
     */
    Matrix translate(const Vector3D &vec);

    /**
     * Apply a transformation to all points in a given figure.
     * @param figure : Figure containing all the points
     * @param matrix : Matrix describing the transformation
     */
    void applyTransformation(Figure& figure, const Matrix &matrix);

    /**
     * Apply a transformation to all points in all given figures.
     * @param figures : Vector of figures containing all the figures
     * @param matrix : Matrix describing the transformation
     */
    void applyTransformation(FiguresList3D& figures, const Matrix &matrix);

    /**
     * Create a matrix that describes the eye-point transformation
     * @param eye : Eye point
     * @return : new matrix
     */
    Matrix EyePointTransformation(const Vector3D &eye);

    /**
     * Project a 3D point on a face at distance d and return as a 2D point.
     * @param point : 3D point to project
     * @param d : distance
     * @return : resulting 2D point
     */
    Point2D *doProjection(const Vector3D &point, const double d);

    /**
     * Project 3D figures on a 2D canvas.
     * @param figures : list of 3D figures
     * @return : list of 2D lines
     */
    LinesList2D doProjection(const FiguresList3D &figures);

    /**
     * Getter for 'info'.
     * @return : info
     */
    const ImageInfo *getInfo() const;
};

#endif //ENGINE_3DLINEDRAWINGS_H
