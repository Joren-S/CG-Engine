//
// Created by joren on 1/04/2018.
//

#ifndef ENGINE_2DLSYSTEMS_H
#define ENGINE_2DLSYSTEMS_H

#include <iostream>
#include <fstream>
#include <list>

#include "../easy_image/easy_image.h"
#include "../l_parser/l_parser.h"

#include "types.h"
#include "input.h"

using namespace std;
typedef std::list<Line2D*> Lines2D;


img::EasyImage ParseLines(const Lines2D &lines, const int size);
LParser::LSystem2D *ParseL2D(const string &pathToL2D);


#endif //ENGINE_2DLSYSTEMS_H
