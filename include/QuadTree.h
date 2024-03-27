#ifndef _QUADTREE_
#define _QUADTREE_

#include <algorithm>
#include <cfloat>
#include <climits>
#include <vector>


#include "ZBuffer.h"
#include "Polygon.h"
#include "Octree.h"
#include "Pixel.h"
#include "AABB.h"

/**
 * @brief 四叉树节点类
 * 
 */
class QuadTreeNode{
    private:
        //包围盒
        AABB aabb;

        //即四颗子树z值中的最小值
        float z;
        
        ZBuffer* zbuffer;
        //子节点序列
        std::vector<QuadTreeNode *> children;
    public:
        //递归构造函数
        QuadTreeNode(int minX, int maxX, int minY, int maxY,ZBuffer* zbuffer);
        QuadTreeNode();
        ~QuadTreeNode();
        
        //包含测试
        bool contain(Pixel &pixel);
        bool contain(Polygon &polygon);
        bool contain(OctreeNode &octreeNode);
        //更新z值
        void update();
        //扫描转化八叉树
        void scanOctree(OctreeNode *OctreeNode);
        //扫描转化一个多边形
        void scanPolygon(Polygon &polygon);
        //绘制像素  
        void addPixels(std::vector<Pixel> &pixels);

        std::vector<QuadTreeNode *> Getchildren();
};

/**
 * @brief 四叉树
 * 
 */
class QuadTree {
    private:
        //根节点
        QuadTreeNode* root;
        int height;
        int width;
    public:
        QuadTree(int width, int height,ZBuffer* zbuffer);
        ~QuadTree();
        QuadTree();
        QuadTreeNode* Getroot();

        static ZBuffer* zbuffer;
};

#endif