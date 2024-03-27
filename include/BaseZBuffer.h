#ifndef _BASE_Z_BUFFER_
#define _BASE_Z_BUFFER_

#include <cfloat>
#include <vector>

#include "Vertex.h"
#include "ZBuffer.h"
#include "Model.h"
/**
 * @brief 最原始的ZBuffer算法，使用了与屏幕像素矩阵一致大小的深度缓冲
 *        对每个物体的像素进行绘制，没有利用任何图像和景物空间相关信息
 */
class BaseZBuffer : public ZBuffer {
    public:
        
        //width*height的深度缓存
        std::vector<std::vector<float>> zBuffer;
        
        BaseZBuffer(int width, int height,Model model);
        ~BaseZBuffer() override;
        void scan() override;
};

#endif