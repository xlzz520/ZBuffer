#ifndef PIXEL_H
#define PIXEL_H

#include<Eigen/Eigen>

class Pixel {
    private:
        int x, y;
        float z;
        Eigen::RowVector3d color;
    public:
        Pixel(int x, int y, float z, Eigen::RowVector3d color);
        ~Pixel();
        int getX();
        int getY();
        float getZ();
        Eigen::RowVector3d getColor();
};

#endif