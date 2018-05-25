//
// Created by joren on 21/04/2018.
//

#ifndef ENGINE_2DLINEDRAWINGS_H
#define ENGINE_2DLINEDRAWINGS_H


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

// authored
#include "types.h"
#include "input.h"

class LineDrawing2D {
private:

    /**
     * Info about the drawing
     */
    const ImageInfo *info;

public:
    /**
     * Constructor
     * @param imgInfo : ImageInfo object containing specifications for the drawing.
     */
    LineDrawing2D(const ImageInfo *imgInfo);

    /**
     * Converts a list of 2D Lines into an EasyImage with specifications from 'info'.
     * @param lines : list of 2D lines that need to be drawn
     * @return : resulting EasyImage
     */
    img::EasyImage LinesToImage(const LinesList2D &lines);

    /**
     * Getter for 'info'.
     * @return : info
     */
    const ImageInfo *getInfo() const;
};


#endif //ENGINE_2DLINEDRAWINGS_H
