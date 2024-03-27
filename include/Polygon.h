#ifndef _POLYGON_
#define _POLYGON_

#include <climits>
#include <cfloat>
#include <vector>

#include "Vertex.h"
#include "Edge.h"
/**
 * @brief 多边形
 * 
 */
class Polygon {
    private:
        //x,y,z均为多边形各坐标最大值，deltaX,Y,Z为最大值减最小值
        int x, deltaX, y, deltaY;
        //z为多边形最大z值
        float z, deltaZ;
        //边序列
        std::vector<Edge> edges;
        //多边形颜色
        Eigen::RowVector3d color;

    public:
        Polygon(std::vector<Vertex> &vertices, int width, int height);
        ~Polygon();

        int getX();
        int getDeltaX();
        int getY();
        int getDeltaY();
        float getZ();
        float getDeltaZ();
        Eigen::RowVector3d getColor();
        std::vector<Edge>& getEdges();
        void SetColor(Eigen::RowVector3d color);        
        bool operator <(const Polygon &polygon)const;
};

#endif