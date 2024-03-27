#include "Pixel.h"

Pixel::Pixel(int x, int y, float z,Eigen::RowVector3d color) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->color = color;
}

Pixel::~Pixel() {}

int Pixel::getX() {
    return x;
}

int Pixel::getY() {
    return y;
}

float Pixel::getZ() {
    return z;
}

Eigen::RowVector3d Pixel::getColor() {
    return color;
}