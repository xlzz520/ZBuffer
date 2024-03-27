#ifndef _FULLHIZ_
#define _FULLHIZ_

#include <algorithm>
#include <cfloat>
#include <vector>

#include "Vertex.h"
#include "ZBuffer.h"
#include "QuadTree.h"
#include "Octree.h"
#include "Polygon.h"
#include "Model.h"

class FullHiz : public ZBuffer{
    public:
        FullHiz(int width, int height,Model model);
        ~FullHiz() override;
        //八叉树存储模型
        Octree* octree;
         //四叉树存储zbuffer
        QuadTree* hizbuffer;
        void scan() override;
};

#endif