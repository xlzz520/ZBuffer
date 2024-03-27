#ifndef _QUADZBUFFER_
#define _QUADZBUFFER_

#include <iostream>
#include "Pixel.h"
#include "ZBuffer.h"
#include "AABB.h"
#include "Octree.h"
/**
 * @brief  非递归结构的四叉树z-buffer
 *         
 */
class QuadZbuffer
{
    private:
        ZBuffer* zbuffer;
        int width,height;
        //存储每一层的zbuffer
        std::vector<float*> zbuffers_;  
        // 每一层z-buffer的宽度
        std::vector< int > zbuffer_len_;  

    public:
        QuadZbuffer(int width, int hight,ZBuffer* zbuffer);
        ~QuadZbuffer();
        //获取包含当前屏幕上包围盒的最小四叉树节点对应在zbuffer上的坐标
        int getHeight(int x_max, int x_min, int y_max, int y_min, int &x, int &y);
       
        //深度测试
        bool DepthTest(int x_max, int x_min, int y_max, int y_min, float z);

        //扫描转化八叉树
        void scanOctree(OctreeNode *OctreeNode);
        //扫描转化一个多边形
        void scanPolygon(Polygon &polygon);
        //增加像素
        void addPixels(std::vector<Pixel> &pixels);
        //深度测试，为真时可被渲染显示
        bool DepthTest(int x_max, int x_min, int y_max, int y_min, int &x, int &y,float z);
};
#endif