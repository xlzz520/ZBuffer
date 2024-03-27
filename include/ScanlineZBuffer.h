#ifndef SCANLINE_Z_BUFFER_H
#define SCANLINE_Z_BUFFER_H

#include <algorithm>
#include <cfloat>
#include <vector>
#include <map>


#include "Vertex.h"
#include "Polygon.h"
#include "ActivePolygon.h"
#include "Segments.h"
#include "ZBuffer.h"
/**
 * @brief 扫描线zbuffer算法，使用了一个长度等于屏幕像素宽度的深度缓冲
 * 
 */
class ScanlineZBuffer : public ZBuffer {
public:
    ScanlineZBuffer(int width, int height,Model model);
    ~ScanlineZBuffer() override;
    
    //缓冲
    std::vector<float> zBuffer;

    void scan() override;
};

#endif