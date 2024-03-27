#include "FullHiz.h"

FullHiz::FullHiz(int width, int height,Model model) : ZBuffer(width, height,model) {}

FullHiz::~FullHiz() {}

void FullHiz::scan() {
    //构建四叉树
    hizbuffer = new QuadTree(width,height,this);
    
    //构建八叉树
    octree = new Octree(polygons,width,height);
    
    //扫描转化
    (hizbuffer->Getroot())->scanOctree(octree->Getroot());
}