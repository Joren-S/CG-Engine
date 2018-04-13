//
// Created by joren on 1/04/2018.
//

#ifndef ENGINE_2DLSYSTEMS_H
#define ENGINE_2DLSYSTEMS_H

#include <list>
#include "types.h"
#include "../easy_image/easy_image.h"


typedef std::list<Line2D*> Lines2D;

img::EasyImage DrawLines(const Lines2D &lines, const int size);

#endif //ENGINE_2DLSYSTEMS_H
