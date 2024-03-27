#ifndef _ACTIVE_EDGE_
#define _ACTIVE_EDGE_

#include "Edge.h"
/**
 * @brief 活化边
 *        与Edge定义基本类似，可以理解为上端点不断变化的Edge
 *        x为与当前扫描线相交的上端点横坐标
 */
class ActiveEdge {
    private:
        //与Edge定义完全相同     s记录累计变化量用来更新活化边
        int x, deltaX, deltaY, s;
        //z为上端点z值
        float z, dz;
        //颜色
        Eigen::RowVector3d color;

    public:
        ActiveEdge();
        ActiveEdge(Edge &edge);
        ~ActiveEdge();
        int getX();
        float getZ();
        //y减1时，更新x、z
        void update();
        Eigen::RowVector3d getColor();
};

#endif