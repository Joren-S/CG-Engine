//
// Created by Joren on 23/03/2018.
//
#include <iostream>
#include <string>

#include "../headers/input.h"

using namespace std;

ImageInfo::ImageInfo(const ini::Configuration &config){
    setType(Default);
    setProperties(new ImageProperties);
    getProperties()->width = config["ImageProperties"]["width"].as_double_or_die();
    getProperties()->height = config["ImageProperties"]["height"].as_double_or_die();
}

// Getters and setters

ImageType ImageInfo::getType() const {
    return type;
}

ImageProperties *ImageInfo::getProperties() const {
    return properties;
}

void ImageInfo::setType(ImageType type) {
    ImageInfo::type = type;
}

void ImageInfo::setProperties(ImageProperties *properties) {
    ImageInfo::properties = properties;
}
