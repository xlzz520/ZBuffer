#ifndef VERTEX_H
#define VERTEX_H

#include <Eigen/Eigen>

class Vertex {
    public:
        //        点的位置   
        Eigen::RowVector3d position;
        Vertex(Eigen::RowVector3d _position):position(_position){};
        ~Vertex(){};
};

#endif