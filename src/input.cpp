//
// Created by Joren on 23/03/2018.
//
#include <iostream>

#include "../headers/input.h"

using namespace std;

ImageInfo::ImageInfo(const ini::Configuration &config){
    // General section
    setType(StrToIT(config["General"]["type"].as_string_or_die()));
    setSize(config["General"]["size"].as_int_or_die());
    vector<double> bg_color = config["General"]["backgroundcolor"].as_double_tuple_or_die();
    setBGColor(DoubleToRGB(&bg_color));

    // 2DLSystem
    LS2D_Properties *LS2D_Prop = new LS2D_Properties();
    vector<double> ls2d_color = config["2DLSystem"]["color"].as_double_tuple_or_die();
    LS2D_Prop->pathToFile = config["2DLSystem"]["inputfile"].as_string_or_die();
    LS2D_Prop->color = DoubleToRGB(&ls2d_color);
    setLS2DProperties(LS2D_Prop);
}


// Help functions

ImageType ImageInfo::StrToIT(string config_line) const {
    /* String -> ImageType (enum)
     * */
    if (config_line == "2DLSystem") {
        return LSys2D;
    }
    return Invalid;
}

ColorRGB* ImageInfo::DoubleToRGB(vector<double> *rgb_as_doubles) {
    ColorRGB *rgb = new ColorRGB();
    if (rgb_as_doubles != NULL) {
        rgb->r = rgb_as_doubles->at(0) * 255;
        rgb->g = rgb_as_doubles->at(1) * 255;
        rgb->b = rgb_as_doubles->at(2) * 255;
    }
    return rgb;
}

// Getters and setters

ImageType ImageInfo::getType() const {
    return type;
}

void ImageInfo::setType(ImageType type) {
    ImageInfo::type = type;
}

int ImageInfo::getSize() const {
    return size;
}

void ImageInfo::setSize(int size) {
    ImageInfo::size = size;
}

ColorRGB *ImageInfo::getBGColor() const {
    return bg_color;
}

void ImageInfo::setBGColor(ColorRGB *bgc) {
    ImageInfo::bg_color = bgc;
}

LS2D_Properties* ImageInfo::getLS2DProperties() const {
    return ls2dProperties;
}

void ImageInfo::setLS2DProperties(LS2D_Properties *prop) {
    ImageInfo::ls2dProperties = prop;
}