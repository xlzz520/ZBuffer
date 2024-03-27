#include "Segments.h"

Segment::Segment(int x, int deltaX, float z, float dz, Eigen::RowVector3d color) {
    this->x = x;
    this->deltaX = deltaX;
    this->z = z;
    this->dz = dz;
    this->color=color;
}

Segment::~Segment() {}

int Segment::getX() {
    return x;
}

int Segment::getDeltaX() {
    return deltaX;
}

float Segment::getZ() {
    return z;
}

float Segment::getDz() {
    return dz;
}

Eigen::RowVector3d Segment::getColor(){
    return color;
}
