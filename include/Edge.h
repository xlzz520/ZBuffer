#ifndef _EDGE_
#define _EDGE_

#include <algorithm>

#include "Vertex.h"

class Edge {
    private:
        //整数值int -----  x，y上端点的屏幕坐标,deltaX、deltaY为线段从下端点到上端点的屏幕坐标值x和y的变化
        // deltaY也可以反应当前线段穿过的剩余的扫描线数量
        int x, deltaX, y, deltaY;
        //浮点数float ----- z为上端点的深度值，dz为y减1时z值的变化
        float z, dz;
        //p为上端点的原始空间坐标,dp为y减1时p的变化量,color为颜色
        Eigen::RowVector3d color;

    public:
        Edge(Vertex &source, Vertex &target, int width, int height,Eigen::RowVector3d color);
        Edge();
        ~Edge();
        //依次按照屏幕坐标y,x对边进行排序
        bool operator <(const Edge &edge) const;
        int getX();
        int getDeltaX();
        int getY();
        int getDeltaY();
        float getZ();
        float getDz();
        Eigen::RowVector3d getColor();
};

#endif
