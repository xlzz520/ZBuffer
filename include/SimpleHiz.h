#ifndef _SIMPLEHIZ_
#define _SIMPLEHIZ_

#include <vector>

#include "Vertex.h"
#include "ZBuffer.h"
#include "QuadTree.h"
#include "Polygon.h"
/**
 * @brief 简单模式的层次zbuffer，只将原来的全分辨率zbuffer改为四叉树zbuffer
 * 
 */
class SimpleHiz : public ZBuffer {

    public:
        SimpleHiz(int width, int height,Model Model);
        ~SimpleHiz() override;
        
        //四叉树
        QuadTree* hizbuffer;
        void scan() override;
};

#endif