//
// Created by joren on 5/05/2018.
//

#include "../headers/3DLineDrawings.h"

LineDrawing3D::LineDrawing3D(const ImageInfo *imgInfo) {
    info = imgInfo;
}

Matrix LineDrawing3D::scaleFigure(const double scale) {

    Matrix Ms = Matrix();
    for (uint i = 1; i < 4; i++) {
        Ms(i, i) = scale;
    }
    return Ms;
}

Matrix LineDrawing3D::rotateX(const double angle) {
    Matrix Mx = Matrix();
    Mx(2, 2) = cos(angle);
    Mx(2, 3) = sin(angle);
    Mx(3, 2) = -sin(angle);
    Mx(3, 3) = cos(angle);
    return Mx;
}

Matrix LineDrawing3D::rotateY(const double angle) {
    Matrix My = Matrix();
    My(1, 1) = cos(angle);
    My(1, 3) = -sin(angle);
    My(3, 1) = sin(angle);
    My(3, 3) = cos(angle);
    return My;
}

Matrix LineDrawing3D::rotateZ(const double angle) {
    Matrix Mz = Matrix();
    Mz(1, 1) = cos(angle);
    Mz(1, 2) = sin(angle);
    Mz(2, 1) = -sin(angle);
    Mz(2, 2) = cos(angle);
    return Mz;
}

Matrix LineDrawing3D::translate(const Vector3D &vec) {
    Matrix Mt = Matrix();
    Mt(4, 1) = vec.x;
    Mt(4, 2) = vec.y;
    Mt(4, 3) = vec.z;
    return Mt;
}

Matrix LineDrawing3D::EyePointTransformation(const Vector3D &eye) {

    Matrix result;

    // setup eye vector and calculate angles
    double r = eye.length();
    double phi = acos(eye.z / r);
    double theta = atan2(eye.y, eye.x);

    // setup matrix and return
    result(1, 1) = -sin(theta);
    result(1, 2) = -cos(theta) * cos(phi);
    result(1, 3) = cos(theta) * sin(phi);
    result(2, 1) = cos(theta);
    result(2, 2) = -sin(theta) * cos(phi);
    result(2, 3) = sin(theta) * sin(phi);
    result(3, 2) = sin(phi);
    result(3, 3) = cos(phi);
    result(4, 3) = -r;

    return result;

}

void LineDrawing3D::applyTransformation(Figure& figure, const Matrix &matrix) {

    for (uint i = 0; i < figure.points.size(); i++) {
        figure.points.at(i) *= matrix;
    }
}

Point2D *LineDrawing3D::doProjection(const Vector3D &point, const double d) {
    double _x = (d * point.x) / (-point.z);
    double _y = (d * point.y) / (-point.z);
    Point2D *result = new Point2D(_x, _y);
    return result;
}

LinesList2D LineDrawing3D::doProjection(FiguresList3D &figures) {

    LinesList2D result;
    Matrix EPT = EyePointTransformation(getInfo()->getLD3DProperties()->eye);

    //cout << getInfo()->getLD3DProperties();
    for (uint fid = 0; fid < getInfo()->getLD3DProperties()->nrFigures; fid++) {
        Figure curFig = figures.at(fid);

        // Convert points to eye-point system.
        applyTransformation(curFig, EPT);

        // Scale
        Matrix S = scaleFigure(curFig.scale);
        applyTransformation(curFig, S);

        // Rotations
        Matrix R = rotateX(curFig.rotateX) * rotateY(curFig.rotateY) * rotateZ(curFig.rotateZ);
        applyTransformation(curFig, R);

        // Translation
        Matrix T = translate(Vector3D::vector(curFig.center));
        applyTransformation(curFig, T);

        // Project the coordinates for all lines.
        double d = 1;
        for (uint lid = 0; lid < curFig.nrLines; lid++) {
            Face curF = curFig.faces.at(lid);
            Vector3D curStart = curFig.points.at(curF.point_indices.at(0));
            Vector3D curEnd = curFig.points.at(curF.point_indices.at(1));

            Line2D *line = new Line2D( doProjection(curStart, 1), doProjection(curEnd, 1) );
            line->color = new ColorRGB( curFig.color.r, curFig.color.g, curFig.color.b);
            result.push_back(line);
        }
    }

    return result;
}

img::EasyImage LineDrawing3D::GenerateImage() {

    // Process system
    LinesList2D Lines = doProjection(getInfo()->getLD3DProperties()->Figures);

    // Convert to EasyImage and return
    LineDrawing2D drawing(getInfo());
    return drawing.LinesToImage(Lines);
}

const ImageInfo *LineDrawing3D::getInfo() const {
    return info;
}