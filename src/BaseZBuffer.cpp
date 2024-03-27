#include "BaseZBuffer.h"
#include "Utils.h"
void BaseZBuffer::scan(){ 
    //清理zBuffer
    zBuffer.resize(width);
    for (std::vector<float> &vector : zBuffer)
        vector = std::vector<float>(height, -FLT_MAX);
    //每个多边形进行扫描
    for (Polygon polygon:polygons)
    {      
        //多边形不能是横线或者竖线
        if (polygon.getDeltaX() > 0 && polygon.getDeltaY() > 0) {
            //获取多边形对应像素
            std::vector<Pixel> pixels = calculatePixels(polygon, 0, width - 1, 0, height - 1);
            for (Pixel &pixel : pixels)
                if (pixel.getZ() > zBuffer[pixel.getX()][pixel.getY()]) {
                    //更新z-buffer
                    zBuffer[pixel.getX()][pixel.getY()] = pixel.getZ();
                    setPixelcolor(pixel);
                }
        }
    }
}


BaseZBuffer::BaseZBuffer(int width, int height,Model model) : ZBuffer(width, height,model) {}

BaseZBuffer::~BaseZBuffer() {}
