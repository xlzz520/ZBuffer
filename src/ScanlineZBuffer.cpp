#include "ScanlineZBuffer.h"
#include "Utils.h"
//参考了

ScanlineZBuffer::ScanlineZBuffer(int width, int height, Model model) : ZBuffer(width, height,model) {}

ScanlineZBuffer::~ScanlineZBuffer() {}


void  ScanlineZBuffer::scan() {
    //初始化深度缓冲
    zBuffer.resize(width);    
    //多边形按照y值从大到小排序
    std::sort(polygons.begin(), polygons.end());
    //活化多边形表
    std::multimap<int, ActivePolygon> activePolygons;
    //从最大y值从上到下扫描

    for (int index = 0, scanlineY = polygons.begin()->getY(); scanlineY >=0; ) {
        //清理深度缓冲
        fill(zBuffer.begin(),zBuffer.end(),-FLT_MAX);
        /*更新活化多边形表
         * 
         */
        //1. 如果扫描线碰到新的多边形，则将其加入活化多边形表
        for (; index < polygons.size() && polygons[index].getY() == scanlineY; index++){
            //多边形不能是横线或者竖线
            if (polygons[index].getDeltaX() > 0 && polygons[index].getDeltaY() > 0) {
                int first=polygons[index].getY()-polygons[index].getDeltaY();

                activePolygons.insert(std::make_pair(first, ActivePolygon(polygons[index])));
            }
        }

        //2. 如果扫描线到达活化多边形的活化边的末尾，将仍然属于同一多边形的其他边则将其作为新的活化边
        for (std::pair<const int, ActivePolygon> &pair : activePolygons)
            pair.second.check(scanlineY);      
        
        //依次遍历活化多边形表，根据其中的 活化边表对 获得当前待扫描的扫描线片段
        for (std::pair<const int, ActivePolygon> &pair : activePolygons) {
            Segment segment = pair.second.segment();
            int startx=segment.getX();
            int endx = segment.getX() + segment.getDeltaX();
            float z=segment.getZ();
            float dz=segment.getDz();
            for (int scanlineX = startx; scanlineX <= endx && scanlineX < width; scanlineX++) {
                if (scanlineX >= 0 && z > zBuffer[scanlineX]) {
                    zBuffer[scanlineX] = z;
                    setPixelcolor(scanlineX, scanlineY, pair.second.getColor());
                }
                z+=dz;
            }
        }

        //清理掉那些已经到达最小y值的活化多边形
        while (!activePolygons.empty() && activePolygons.rbegin()->first == scanlineY){
            std::multimap<int, ActivePolygon>::iterator it=activePolygons.end();
            activePolygons.erase(--it);
        }

        //利用图形连续性对每个多边形的活化边进行更新
        for (std::pair<const int, ActivePolygon> &pair : activePolygons)
            pair.second.update();

        //加速循环，若活化多边形表为空则直接找到下一个y值继续扫描（可以跳过一些不必要的y值）
        if (activePolygons.empty())
            scanlineY = index < polygons.size() ? polygons[index].getY() : -1;
        else
            scanlineY--;
    }
}