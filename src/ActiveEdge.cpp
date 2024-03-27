#include "ActiveEdge.h"
//活化多边形表借鉴了 https://github.com/Wajov/HiddenSurfaceRemover/blob/master/src/Polygon.cpp 的设计
//本项目很多数据结构也参考了许多网上的开源代码，但不同之处在于本项目是基于Eigen库进行设计的，并且去除了一些只对渲染
//有用，而对实现算法无关紧要的相关数据项

ActiveEdge::ActiveEdge() {}

ActiveEdge::ActiveEdge(Edge &edge) {
    color=edge.getColor();
    x = edge.getX();
    deltaX = edge.getDeltaX();
    deltaY = edge.getDeltaY();
    z = edge.getZ();
    dz = edge.getDz();
    s = 0;
}

ActiveEdge::~ActiveEdge() {}

int ActiveEdge::getX() {
    return x;
}

float ActiveEdge::getZ() {
    return z;
}


//满足 deltaX/deltaY = x坐标变化值/-1（y从上到下扫描不断减1,x随之变换）
//即   deltaY=deltaX*x坐标变化值
//用s记录累计变换量，参考代码：https://github.com/Wajov/HiddenSurfaceRemover/blob/master/src/ActiveEdge.cpp
//s一次增加deltaX个单位，若大于deltaY,则x左边变换一次，并且累积量s减去deltaY
//                    若小于delaY,积累量不够，此时x不变化

//不同之处在于：deltaY为右下点减去左上点的y值变化
//此处y按照从大到小排列，deltaY<=0
void ActiveEdge::update() {

    if (deltaX < 0)
        for (s += deltaX; s <= deltaY; s -= deltaY)
            x--;
    else
        for (s += deltaX; s >= -deltaY; s +=deltaY)
            x++;
    
    z += dz;
}

Eigen::RowVector3d ActiveEdge::getColor(){
    return color;
}
