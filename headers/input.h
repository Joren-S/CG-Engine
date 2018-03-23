//
// Created by Joren on 23/03/2018.
//

#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include "../ini_configuration/ini_configuration.h"

enum ImageType { Default };

struct ImageProperties {
    double width, height;
};

class ImageInfo {

private:
    ImageType type;
    ImageProperties *properties;

public:
    ImageInfo(const ini::Configuration &config);

    // Getters and setters

    ImageType getType() const;
    ImageProperties *getProperties() const;

    void setType(ImageType type);
    void setProperties(ImageProperties *properties);
};


#endif //ENGINE_INPUT_H
