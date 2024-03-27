#include "ActivePolygon.h"
//本项目许多数据结构都看参考了开源代码，活化多边形表的设计参考了：https://github.com/Wajov/HiddenSurfaceRemover/blob/master/src/ActivePolygon.cpp
//不同之处，对于多边形中的横线，本项目没有直接采取丢弃的方式，而是判断有几条横线
//      1条横线：可以用另外两条边构成活化多边形表，与寻常构建无异
//      3条横线：（比如有些面片不是三角形而是一条件直线上的三个点，不可能有两条横线）， 
//               直接用该条横线的左右端点来构建活化多边形



ActivePolygon::ActivePolygon(Polygon &polygon) {
    std::vector<Edge> edgesTemp = polygon.getEdges();
    //
    for (Edge &edge : edgesTemp)
        if (edge.getDeltaY() != 0 )
            edges.push_back(edge);
    //不全是横线
    // if(edges.size()!=0){
    //     //按照上端点 左上优先 的原则进行边的排序
    std::sort(edges.begin(), edges.end());
    index = 0;
    leftY = edges[index].getY() + edges[index].getDeltaY();
    leftEdge = ActiveEdge(edges[index++]);
    rightY = edges[index].getY() + edges[index].getDeltaY();
    rightEdge = ActiveEdge(edges[index++]);
    color=polygon.getColor();      
    // }else{
        // for (Edge &edge : edgesTemp)
        //         edges.push_back(edge);
        // std::sort(edges.begin(), edges.end());
        // leftY = edges[0].getY() + edges[0].getDeltaY();
        // leftEdge = ActiveEdge(edges[0]);
        // rightY = edges[2].getY() + edges[2].getDeltaY();
        // rightEdge = ActiveEdge(edges[2]);
        // index=2;
    // 

}

ActivePolygon::~ActivePolygon() {}


void ActivePolygon::check(int scanline) {
    while (index < edges.size() && (leftY == scanline || rightY == scanline)) {
        if (leftY == scanline) {
            leftY = edges[index].getY() + edges[index].getDeltaY();
            leftEdge = ActiveEdge(edges[index++]);
        }
        if (rightY == scanline) {
            rightY = edges[index].getY() + edges[index].getDeltaY();
            rightEdge = ActiveEdge(edges[index++]);
        }
    }

    if (leftEdge.getX() > rightEdge.getX()) {
        std::swap(leftY, rightY);
        std::swap(leftEdge, rightEdge);
    }
}

void ActivePolygon::update() {
    leftEdge.update();
    rightEdge.update();
}

Segment ActivePolygon::segment() {
    int deltaX = rightEdge.getX() - leftEdge.getX();
    float dz = (rightEdge.getZ() - leftEdge.getZ()) / deltaX;

    return Segment(leftEdge.getX(), deltaX, leftEdge.getZ(), dz,color);
}
Eigen::RowVector3d ActivePolygon::getColor(){
    return color;
}