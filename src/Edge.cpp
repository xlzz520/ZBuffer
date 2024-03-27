#include "Edge.h"

Edge::Edge(Vertex &source, Vertex &target, int width, int height,Eigen::RowVector3d color) {
    
    color=color;
    
    Vertex s = source, t = target;
    //交换使得y值大的在前面
    if (s.position.y() < t.position.y()) {
        std::swap(s, t);
    }
    
    int x1, y1, x2, y2;
    //空间坐标系转屏幕坐标系，仍然保持相对位置关系
    x1 = (int)((s.position.x() + 0.5f) * width);
    y1 = (int)((s.position.y()+ 0.5f)  * height);
    x2 = (int)((t.position.x()+ 0.5f)  * width);
    y2 = (int)((t.position.y() + 0.5f) * height);

    //x,y为上端点屏幕坐标,z为上端点深度值
    x = x1;
    deltaX = x2 - x1;
    //deltaY<=0
    y = y1;
    deltaY = y2 - y1;
    z = s.position.z();
    dz = (s.position.z() - t.position.z()) / deltaY;

}

Edge::~Edge() {}
Edge::Edge(){}
//左上优先
bool Edge::operator <(const Edge &edge) const{
    //屏幕坐标系中y值大的排在前面
    if (y != edge.y)
        return y > edge.y;
    else if (y + deltaY != edge.y + edge.deltaY)
        return y + deltaY > edge.y + edge.deltaY;
    //屏幕坐标系中x值小的排在前面
    else if (x != edge.x)
        return x < edge.x;
    else
        return x + deltaX < edge.x + edge.deltaX;
}

int Edge::getX() {
    return x;
}

int Edge::getDeltaX() {
    return deltaX;
}

int Edge::getY() {
    return y;
}

int Edge::getDeltaY() {
    return deltaY;
}

float Edge::getZ() {
    return z;
}

float Edge::getDz() {
    return dz;
}

Eigen::RowVector3d Edge::getColor(){
    return color;
}
