#include "Polygon.h"

Polygon::Polygon(std::vector<Vertex> &vertices, int width, int height) {

    //构建边序列
    for (int i = 0; i < vertices.size() - 1; i++) {
        edges.push_back(Edge(vertices[i], vertices[i + 1], width, height,color));
    }
    edges.push_back(Edge(*vertices.rbegin(), *vertices.begin(), width, height,color));
    
    //获取到多边形边的最大最小坐标值
    int minX, maxX, minY, maxY;
    minX = minY = INT_MAX;
    maxX = maxY = INT_MIN;
    float minZ = FLT_MAX, maxZ = -FLT_MAX;
    for (Edge &edge : edges) {
        maxY = std::max(maxY, edge.getY());
        minY = std::min(minY, edge.getY() + edge.getDeltaY());
        
        minX = std::min(minX, std::min(edge.getX(), edge.getX() + edge.getDeltaX()));
        maxX = std::max(maxX, std::max(edge.getX(), edge.getX() + edge.getDeltaX()));

        minZ = std::min(minZ, std::min(edge.getZ(), edge.getZ() + edge.getDz() * edge.getDeltaY()));
        maxZ = std::max(maxZ, std::max(edge.getZ(), edge.getZ() + edge.getDz() * edge.getDeltaY()));
    } 
    
    x = maxX;
    deltaX = maxX - minX;
    y = maxY;
    deltaY = maxY - minY;
    z = maxZ;
    deltaZ = maxZ - minZ;
}

Polygon::~Polygon() {}

bool Polygon::operator <(const Polygon &polygon)const {
    if (y != polygon.y)
        return y > polygon.y;
    else
        return y + deltaY < polygon.y + polygon.deltaY;
}

int Polygon::getX() {
    return x;
}

int Polygon::getDeltaX() {
    return deltaX;
}

int Polygon::getY() {
    return y;
}

int Polygon::getDeltaY() {
    return deltaY;
}

float Polygon::getZ() {
    return z;
}

float Polygon::getDeltaZ() {
    return deltaZ;
}

std::vector<Edge>& Polygon::getEdges() {
    return edges;
}

Eigen::RowVector3d Polygon::getColor(){
    return color;
}

void Polygon::SetColor(Eigen::RowVector3d color){
    this->color=color;
}