//
// Created by joren on 1/04/2018.
//

#ifndef ENGINE_2DLSYSTEMS_H
#define ENGINE_2DLSYSTEMS_H

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

class LSystem2D {
private:
    /**
     * Parsed LSystem, NULL if incomplete/errors/...
     */
    const LParser::LSystem2D *ls2d;

    /**
     * Info about the LSystem, NULL if incomplete/errors/...
     */
    const ImageInfo *info;

public:
    /**
     * Constructor, parses the L2D file and stores the result in ls2d.
     * @param pathToL2D : Path to the L2D file.
     * @param imgInfo : ImageInfo object containing specifications for the LSystem.
     */
    LSystem2D(const ImageInfo *imgInfo);

    /**
     * Processes the L-System and determines the lines that need to be drawn.
     * @return : List of 2D lines that need to be drawn.
     */
    LinesList2D ProcessLSystem();

    /**
     * Converts a list of 2D Lines into an EasyImage with specifications from 'info'.
     * @param lines : list of 2D lines that need to be drawn
     * @return : resulting EasyImage
     */
    img::EasyImage LinesToImage(const LinesList2D &lines);

    /**
     * Processes the L-system and generates an EasyImage.
     * This function packs 'ProcessLSystem' and 'LinesToImage' into 1 easy-to-use function.
     * @return resulting EasyImage
     */
    img::EasyImage GenerateImage();

    /**
     * Checks if a character is in the alphabet.
     * @param _char : character to check
     * @return : Boolean if character is present or not
     */
    const bool isInAlphabet(char _char);

    /**
     * Builds 1 single easy-to-use rule by iterating n amount of times (specified in info).
     * Uses recursion to build the rule.
     * @param curRule : current rule after iteration n
     * @param curIteration : current iteration n
     * @return : fully built rule
     */
    std::string buildRule(std::string curRule = std::string(), int curIteration = 0);

    /**
     * Finds the next point, given a length and angle, using trigonometry.
     * @param start : 2D starting point
     * @param angle : Angle to move at
     * @param length : Length to move
     * @return : Resulting 2D Point
     */
    Point2D FindNextPoint(Point2D start, double angle, uint length);

    // Getters
    /**
     * Getter for 'ls2d'.
     * @return : ls2D
     */
    const LParser::LSystem2D *getLSystem() const;

    /**
     * Getter for 'info'.
     * @return : info
     */
    const ImageInfo *getInfo() const;
};

#endif //ENGINE_2DLSYSTEMS_H
