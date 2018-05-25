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

class LineDrawing3D {
private:
    const ImageInfo *info;

public:

    /**
     * Constructor.
     * @param imgInfo : ImageInfo object containing specifications for the LSystem.
     */
    LineDrawing3D(const ImageInfo *imgInfo);

    /**
     * Rotates and translates all the points in a figure so the eye is the new origin.
     * ECS = Eye-Coordinate System.
     * @param figure_id : id of the figure.
     */
    void PointsToECS(int figure_id = 0);

    /**
     * Converts the 3D system into a 2D system (projection)?
     * @param figure_id : id of the figure.
     * @return
     */
    vector<Point2D*> PerspectiveProjection(int figure_id = 0);


    tuple<uint, uint> CalculateImageProperties(int figure_id = 0);

    /**
     * Converts a list of 3D/2D Lines (z will be constant d) into an EasyImage with specifications from 'info'.
     * @param figure_id : id of the figure.
     * @return : resulting EasyImage
     */
    img::EasyImage LinesToImage(int figure_id = 0);

    /**
     * Processes the Line Drawing and generates an EasyImage.
     * This function packs 'PointsToECS', 'PerspectiveProjection' and 'LinesToImage' into 1 easy-to-use function.
     * @param figure_id : id of the figure.
     * @return resulting EasyImage
     */
    img::EasyImage GenerateImage(int figure_id = 0);

    /**
     * Getter for 'info'.
     * @return : info
     */
    const ImageInfo *getInfo() const;
};

#endif //ENGINE_3DLINEDRAWINGS_H
