#include "Octree.h"

//Octree设计参考了 https://github.com/Wajov/HiddenSurfaceRemover/blob/master/src/Octree.cpp  中关于Octree 的设计，这种设计其实是一种通用的设计
//代码改进之处在于：
//1. 将八叉树节点和八叉树定义分离开，同时将八叉树节点与AABB这一数据结构联系起来，使代码思路更清晰
//2. 八叉树的子节点添加顺序不同，原链接子节点的添加顺序十分随意，我认为应该将z值可能大的子节点尽可
//   能先扫描，以期尽可能早地使四叉树zbuffer较大，达到"快速拒绝”，例如先扫描前面的四个节点再扫描后续的节点
//3. 如果节点太小了就不再进行八叉划分，节省了空间

OctreeNode::OctreeNode(int minX, int maxX, int minY, int maxY, float minZ, float maxZ, std::vector<Polygon> &polygons):OctreeNode(AABB(minX,maxX,minY,maxY,minZ,maxZ),polygons){}

OctreeNode::OctreeNode(AABB aabb, std::vector<Polygon> &polygons){
    
    //递归构建物体的八叉树
    this->aabb=aabb;
    
    //作为叶子节点 -- 当前八叉树节点保护的多边形数量<=设定的阈值（0...threshhold)
    if (polygons.size() <= Octree::THRESHOLD) {
        this->polygons = polygons;
    } else {

        int minX=aabb.getMinX(), maxX=aabb.getMaxX(), minY=aabb.getMinY(),  maxY=aabb.getMaxY();
        float minZ=aabb.getMinZ(), maxZ=aabb.getMaxZ(); 
        
        if(minX+1 >= maxX || minY+1 >= maxY || minZ+1 >= maxZ){
            
            //太小了不需要划分成八个节点，也直接作为一个叶子节点
            this->polygons=polygons;

        }else{  
            
            //划分节点内的多边形
            //  1.遍历左右/前后/上下 组成的8个子节点，若有多边形包含在其中，则将其添加到该节点
            //  2.其余多边形跨越分类面，属于本节点        
            
            int middleX = (minX + maxX) / 2;
            int middleY = (minY + maxY) / 2;
            float middleZ = (minZ + maxZ) /2;      

            // 8个子节点
            // r--right l--left t--top d--down n--near f--far
            // 0-rtn 1-ltn 2-ldn 3-rdn 4-rtf 5-ltf 6-ldf  7-rdf
            AABB rtn(middleX+1,maxX,middleY+1,maxY,middleZ+1,maxZ);
            AABB ltn(minX,middleX,middleY+1,maxY,middleZ+1,maxZ);
            AABB ldn(minX,middleX,minY,middleY,middleZ+1,maxZ);
            AABB rdn(middleX+1,maxX,minY,middleY,middleZ+1,maxZ);
            AABB rtf(middleX+1,maxX,middleY+1,maxY,minZ,middleZ);
            AABB ltf(minX,middleX,middleY+1,maxY,minZ,middleZ);
            AABB ldf(minX,middleX,minY,middleY,minZ,middleZ);
            AABB rdf(middleX+1,maxX,minY,middleY,minZ,middleZ);
            
            std::vector<std::vector<Polygon>> childPolygons(8);
            for (Polygon &polygon : polygons)
                if(rtn.contain(polygon))
                    childPolygons[0].push_back(polygon);
                else
                if(ltn.contain(polygon))
                    childPolygons[1].push_back(polygon);
                else if(ldn.contain(polygon))
                    childPolygons[2].push_back(polygon);
                else if(rdn.contain(polygon))
                    childPolygons[3].push_back(polygon);
                else if(rtf.contain(polygon))
                    childPolygons[4].push_back(polygon);               
                else if(ltf.contain(polygon))
                    childPolygons[5].push_back(polygon);
                else if(ldf.contain(polygon))
                    childPolygons[6].push_back(polygon);              
                else if(rdf.contain(polygon))
                    childPolygons[7].push_back(polygon);
                else    
                    this->polygons.push_back(polygon);
            // 0-rtn 1-ltn 2-ldn 3-rdn 4-rtf 5-ltf 6-ldf  7-rdf
            
            children.push_back(new OctreeNode(rtn, childPolygons[0]));
            children.push_back(new OctreeNode(ltn, childPolygons[1]));
            children.push_back(new OctreeNode(ldn, childPolygons[2]));
            children.push_back(new OctreeNode(rdn, childPolygons[3]));
            children.push_back(new OctreeNode(rtf, childPolygons[4]));
            children.push_back(new OctreeNode(ltf, childPolygons[5]));
            children.push_back(new OctreeNode(ldf, childPolygons[6]));
            children.push_back(new OctreeNode(rdf, childPolygons[7]));

        }
    }
}

OctreeNode::~OctreeNode() {
    for (OctreeNode *child : children)
        delete child;
}
AABB OctreeNode::getAABB(){
    return aabb;
}
std::vector<Polygon> OctreeNode::getPolygons() {
    return polygons;
}

std::vector<OctreeNode *> OctreeNode::getChildren() {
    return children;
}

float OctreeNode::getZ(){
    return aabb.getMaxZ();
}

        
Octree::Octree(std::vector<Polygon> &polygons,int width,int height){
    //Model读取后对所有的三角形面片进行了归一化
    //初始化所有八叉树节点的深度值均在[-1,1]之间
    float minZ=-1,maxZ=1;
    
    this->root=new OctreeNode(0, width-1, 0, height-1, minZ, maxZ, polygons);
    
    this->width=width;
    this->height=height;
}
Octree::Octree(){}

Octree::~Octree(){

    delete root;
}
OctreeNode* Octree::Getroot(){
    return root;
}
