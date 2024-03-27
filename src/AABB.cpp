#include "AABB.h"

//空间坐标包围盒，使用x,y,z
AABB::AABB(int _minX, int _maxX, int _minY, int _maxY, float _minZ, float _maxZ) :
			minX(_minX), maxX(_maxX), minY(_minY), maxY(_maxY), minZ(_minZ), maxZ(_maxZ) {}
//屏幕坐标包围盒,只使用x,y
AABB::AABB(int _minX, int _maxX, int _minY, int _maxY): minX(_minX),maxX(_maxX), minY(_minY), maxY(_maxY){}
AABB::AABB(){}
int AABB::getMinX() {
    return minX;
}

int AABB::getMaxX() {
    return maxX;
}

int AABB::getMinY() {
    return minY;
}

int AABB::getMaxY() {
    return maxY;
}

float AABB::getMinZ(){
    return minZ;
}
float AABB::getMaxZ(){
    return maxZ;
}
bool AABB::contain(int x,int y,float z){
    return minX <=x && maxX >= x && minY <= y && maxY >= y && minZ<=z && minZ>=z;
}
bool AABB::contain(int x,int y){
    return minX <=x && maxX >= x && minY <= y && maxY>= y;
}
bool AABB::contain(int xmin,int xmax,int ymin,int ymax ){
    return minX <= xmin && xmax <= maxX && minY <= ymin && ymax <= maxY;
}
bool AABB::contain(Polygon polygon){
    return minX <= polygon.getX()-polygon.getDeltaX() && maxX >= polygon.getX()  && minY <= polygon.getY() - polygon.getDeltaY() && maxY >= polygon.getY() ;
}
bool AABB::contain(AABB aabb) {
    return minX <= aabb.getMinX() && maxX >= aabb.getMaxX() && minY <=aabb.getMinY() && maxY >= aabb.getMaxY()
            &&minY <= aabb.getMinY() && maxX >= aabb.getMaxX();
}