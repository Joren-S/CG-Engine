//
// Created by Joren on 23/03/2018.
//


#include "../headers/input.h"

using namespace std;

ImageInfo::ImageInfo(const ini::Configuration &config) {

    vector<double> bg_color;
    setType(StrToIT(config["General"]["type"].as_string_or_die()));

    // 2D L-System
    if (getType() == LSys2D) {

        setSize(config["General"]["size"].as_int_or_die());
        bg_color = config["General"]["backgroundcolor"].as_double_tuple_or_die();
        setBGColor(DoubleToRGB(&bg_color));
        LS2D_Properties *LS2D_Prop = new LS2D_Properties();
        vector<double> ls2d_color = config["2DLSystem"]["color"].as_double_tuple_or_die();
        LS2D_Prop->pathToFile = config["2DLSystem"]["inputfile"].as_string_or_die();
        LS2D_Prop->color = DoubleToRGB(&ls2d_color);
        setLS2DProperties(LS2D_Prop);
    }

    // 3D Line drawing
    if (getType() == LDraw3D) {

        setSize(config["General"]["size"].as_int_or_die());
        bg_color = config["General"]["backgroundcolor"].as_double_tuple_or_die();
        setBGColor(DoubleToRGB(&bg_color));

        LD3D_Properties *LD3D_Prop = new LD3D_Properties();
        setLD3DProperties(LD3D_Prop);

        vector<double> eye = config["General"]["eye"].as_double_tuple_or_die();
        LD3D_Prop->eye =  Vector3D::point(eye.at(0), eye.at(1), eye.at(2));
        LD3D_Prop->nrFigures = config["General"]["nrFigures"].as_int_or_die();

        for (uint i = 0; i < LD3D_Prop->nrFigures; i++) {
            stringstream ss;
            ss << "Figure" << i;
            string section = ss.str();

            vector<double> center = config[section]["center"].as_double_tuple_or_die();
            vector<double> ld3d_color = config[section]["color"].as_double_tuple_or_die();

            Figure fig;
            fig.type = config[section]["type"].as_string_or_die();
            fig.scale = config[section]["scale"].as_double_or_die();
            fig.rotateX = config[section]["rotateX"].as_double_or_die();
            fig.rotateY = config[section]["rotateY"].as_double_or_die();
            fig.rotateZ = config[section]["rotateZ"].as_double_or_die();
            fig.center = Vector3D::point(center.at(0), center.at(1), center.at(2));
            fig.color = *DoubleToRGB(&ld3d_color);
            fig.nrPoints = config[section]["nrPoints"].as_int_or_die();
            fig.nrLines = config[section]["nrLines"].as_int_or_die();

            for (uint nP = 0; nP < fig.nrPoints; nP++) {
                ss.str(string());
                ss.clear();
                ss << "point" << nP;
                string pointsection = ss.str();

                vector<double> coord = config[section][pointsection].as_double_tuple_or_die();
                fig.points.push_back(Vector3D::point(coord.at(0), coord.at(1), coord.at(2)));
            }

            for (uint nL = 0; nL < fig.nrLines; nL++) {
                ss.str(string());
                ss.clear();
                ss << "line" << nL;
                string linesection = ss.str();

                Face face;
                face.point_indices = config[section][linesection].as_int_tuple_or_die();
                fig.faces.push_back(face);
            }
            LD3D_Prop->Figures.push_back(fig);
        }
    }
}

// Help functions

ImageType ImageInfo::StrToIT(string config_line) const {
    /* String -> ImageType (enum)
     * */
    if (config_line == "2DLSystem") {
        return LSys2D;
    }
    if (config_line == "Wireframe") {
        return LDraw3D;
    }
    return Invalid;
}

ColorRGB* ImageInfo::DoubleToRGB(vector<double> *rgb_as_doubles) {
    /* [0-1] -> [0-255]
     * */
    ColorRGB *rgb = new ColorRGB(0,0,0);
    if (rgb_as_doubles != NULL) {
        rgb->r = round(rgb_as_doubles->at(0) * 255);
        rgb->g = round(rgb_as_doubles->at(1) * 255);
        rgb->b = round(rgb_as_doubles->at(2) * 255);
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

LD3D_Properties *ImageInfo::getLD3DProperties() const {
    return ld3DProperties;
}

void ImageInfo::setLD3DProperties(LD3D_Properties *prop) {
    ImageInfo::ld3DProperties = prop;
}