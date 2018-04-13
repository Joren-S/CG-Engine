//
// Created by Joren on 23/03/2018.
//

#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include <iostream>
#include <cmath>
#include "../ini_configuration/ini_configuration.h"

#include "types.h"
#include "2DLSystems.h"

using namespace std;

enum ImageType { Invalid, LSys2D };

struct LS2D_Properties {
    string pathToFile;
    ColorRGB *color;
};



class ImageInfo {

private:
    ImageType type;
    int size;
    ColorRGB *bg_color;

    // LS - 2D
    LS2D_Properties *ls2dProperties;

public:
    ImageInfo(const ini::Configuration &config);

    // Getters and setters

    ImageType getType() const;

    void setType(ImageType type);

    int getSize() const;

    void setSize(int size);

    ColorRGB *getBGColor() const;

    void setBGColor(ColorRGB *bgc);

    LS2D_Properties *getLS2DProperties() const;

    void setLS2DProperties(LS2D_Properties *prop);

    // Help functions

    ImageType StrToIT(string config_line) const;

    ColorRGB *DoubleToRGB(vector<double> *rgb_as_doubles);
};


#endif //ENGINE_INPUT_H
