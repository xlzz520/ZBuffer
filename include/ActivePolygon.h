#ifndef ACTIVE_POLYGON_H
#define ACTIVE_POLYGON_H

#include <algorithm>
#include <climits>
#include <vector>
#include <map>

#include "Polygon.h"
#include "Edge.h"
#include "Segments.h"
#include "ActiveEdge.h"
#include <Eigen/Eigen>
/**
 * @brief 活化多边形表
 *        与多边形表相比，多记录了两条活化边的信息
 */        
class ActivePolygon {
    private:
        // 还未活化的边的索引  左右活化边的最小y值
        int index, leftY, rightY;
        //边序列
        std::vector<Edge> edges;
        Eigen::RowVector3d color;
        //活化多边形的左活化边和右活化边
        ActiveEdge leftEdge, rightEdge;
    public:
        ActivePolygon(Polygon &polygon);
        ~ActivePolygon();

        //检查是否有新的活化边：对当前扫描线进行检查，判断是否达到之前左右活化边下端点
        void check(int scanline);
        //对左右活化边更新其x和z
        void update();
        //获取此时活化多边形对应的左右两条活化边在x方向上的夹着的线段
        Segment segment();
        
        Eigen::RowVector3d getColor();
        
};
#endif
