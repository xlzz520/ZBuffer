#include "QuadTree.h"


QuadTreeNode::QuadTreeNode(int minX, int maxX, int minY, int maxY,ZBuffer* zbuffer) {
    
    this->zbuffer=zbuffer;
    //当前四叉树对应屏幕坐标包围盒
    AABB aabb(minX, maxX, minY, maxY);
    this->aabb=aabb;
    //初始层次z-buffer所有值为无穷小
    z = -FLT_MAX;
    //构建四叉树子树
    if (minX != maxX || minY != maxY) {
        int middleX = (minX + maxX) / 2, middleY = (minY + maxY) / 2;
            children.push_back(new QuadTreeNode(minX, middleX, minY, middleY,zbuffer));
        if (middleX + 1 <= maxX)
            children.push_back(new QuadTreeNode(middleX + 1, maxX, minY, middleY,zbuffer));
        if (middleY + 1 <= maxY)
            children.push_back(new QuadTreeNode(minX, middleX, middleY + 1, maxY,zbuffer));
        if (middleX + 1 <= maxX && middleY + 1 <= maxY)
            children.push_back(new QuadTreeNode(middleX + 1, maxX, middleY + 1, maxY,zbuffer));
    }
}
QuadTreeNode::QuadTreeNode(){}

QuadTreeNode::~QuadTreeNode() {
    for (QuadTreeNode *child : children)
        delete child;
}

bool QuadTreeNode::contain(Pixel &pixel) {
    return this->aabb.contain(pixel.getX(),pixel.getY());
}

bool QuadTreeNode::contain(Polygon &polygon) {
    return this->aabb.contain(polygon);
}

bool QuadTreeNode::contain(OctreeNode &octreeNode) {
    AABB aabb=octreeNode.getAABB();
    return this->aabb.contain(aabb.getMinX(),aabb.getMaxX(),aabb.getMinY(),aabb.getMaxY());
}
//更新为子节点的最小值
void QuadTreeNode::update() {
    z = FLT_MAX;
    for (QuadTreeNode *child : children)
        z = std::min(z, child->z);
}

void QuadTreeNode::addPixels(std::vector<Pixel> &pixels) {
    //叶节点直接绘制和更新层次z-buffer
    if (this->aabb.getMinX() == this->aabb.getMaxX() && this->aabb.getMinY() == this->aabb.getMaxY()) {
        for (Pixel &pixel : pixels){
            if (pixel.getZ() > z) {
                z = pixel.getZ();
                zbuffer->setPixelcolor(pixel.getX(), pixel.getY(), pixel.getColor());
            }
        }
    } else {
    //非叶节点，进行递归
        std::vector<std::vector<Pixel>> childPixels(children.size());
        //遍历待绘制的像素，添加到包含其的子节点中
        for (Pixel &pixel : pixels)
            for (int i = 0; i < children.size(); i++)
                if (children[i]->contain(pixel)) {
                    childPixels[i].push_back(pixel);
                    break;
                }
        for (int i = 0; i < children.size(); i++)
            if (!childPixels[i].empty())
                children[i]->addPixels(childPixels[i]);
        //每次绘制完都要更新层次z-buffer
        update();
    }
}

void QuadTreeNode::scanPolygon(Polygon &polygon) {
    //快速拒绝：物体最大深度值小于四叉树节点最小深度值，被遮挡
    if (z >= polygon.getZ())
        return;
    //当前层测试未被遮挡，继续遍历子节点
    bool flag = true;
    for (QuadTreeNode *child : children)
        if (child->contain(polygon)) {
            child->scanPolygon(polygon);
            flag = false;
            break;
        }
    //子节点不包含该多边形，只能直接扫描转化该多边形
    if (flag) {
        std::vector<Pixel> pixels = zbuffer->calculatePixels(polygon, this->aabb.getMinX(), this->aabb.getMaxX(), this->aabb.getMinY(), this->aabb.getMaxY());
        addPixels(pixels);
    }
}

void QuadTreeNode::scanOctree(OctreeNode *octreeNode) {
    //快速拒绝
    if (z >= octreeNode->getZ()) return;

    std::vector<Polygon> polygons = octreeNode->getPolygons();
    
    //绘制当前八叉树节点包含的多边形（一定不被子节点所包含）
    for (Polygon &polygon : polygons) {
        if (polygon.getDeltaX() > 0 && polygon.getDeltaY() >0) {
            std::vector<Pixel> pixels = zbuffer->calculatePixels(polygon, this->aabb.getMinX(), this->aabb.getMaxX(), this->aabb.getMinY(), this->aabb.getMaxY());
            addPixels(pixels);
        }
    }
    //遍历八叉树子树继续进行绘制
    std::vector<OctreeNode *> octreeChildren = octreeNode->getChildren();
    if (octreeChildren.size()!=0)
        //每个子节点
        for (OctreeNode *octreeChild : octreeChildren)
            for (QuadTreeNode *child : children)
                if (child->contain(*octreeChild)){
                    child->scanOctree(octreeChild);
                    break;
                }
}

std::vector<QuadTreeNode *> QuadTreeNode::Getchildren(){
    return children;
}


QuadTree::QuadTree(int width, int height,ZBuffer* zbuffer){
    //构建四叉树
    this->root=new QuadTreeNode(0, width-1, 0, height-1,zbuffer);
    this->width=width;
    this->height=height;
}
QuadTree::QuadTree(){}

QuadTree::~QuadTree(){
    delete root;
}

QuadTreeNode* QuadTree::Getroot(){
    return root;
}
