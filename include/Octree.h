#ifndef _OCTREE_
#define _OCTREE_

#include <algorithm>
#include <vector>

#include "Polygon.h"
#include "AABB.h"


/**
 * @brief 八叉树节点类
 *        每个八叉树节点有一个其内部包含多边形的最大的z值
 */        
class OctreeNode{
    private:
        //层次包围盒
        AABB aabb;
        //子节点
        std::vector<OctreeNode *> children;
        //包含的多边形
        std::vector<Polygon> polygons;
    public:
        OctreeNode(int minX, int maxX, int minY, int maxY, float minZ, float maxZ, std::vector<Polygon> &polygons);
        OctreeNode(AABB aabb, std::vector<Polygon> &polygons);
        ~OctreeNode();
        AABB getAABB();
        //获得当前八叉树节点的最大z值
        float getZ();
        std::vector<Polygon> getPolygons();
        std::vector<OctreeNode *> getChildren();
};
/**
 * @brief 八叉树类
 *        由若干八叉树节点链接而成
 */

class Octree {
    private:
        OctreeNode* root;
        int height;
        int width;
    public:
        //八叉树节点最少包含的多边形数量阈值
        const static int THRESHOLD = 10;
        Octree(std::vector<Polygon> &polygons,int width,int height);
        Octree();
        ~Octree();
        OctreeNode* Getroot();
};
#endif
























// class Octree {
//     private:
//         const int THRESHOLD = 1;
//         int minX, maxX, minY, maxY;
//         float minZ, maxZ, z;
//         std::vector<Polygon> polygons;
//         std::vector<Octree *> children;

//     public:
//         Octree(int minX, int maxX, int minY, int maxY, float minZ, float maxZ, std::vector<Polygon> &polygons);
//         ~Octree();
//         int getMinX();
//         int getMaxX();
//         int getMinY();
//         int getMaxY();
//         float getZ();
//         std::vector<Polygon> getPolygons();
//         std::vector<Octree *> getChildren();
// };

// #endif