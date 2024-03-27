#ifndef Z_BUFFER_H
#define Z_BUFFER_H

#include <cmath>
#include <algorithm>
#include <vector>

#include <Eigen/Eigen>
#include "Vertex.h"
#include "Pixel.h"
#include "Polygon.h"
#include "ActivePolygon.h"
#include "Segments.h"
#include "Model.h"
/**
 * @brief ZBuffer为纯虚基，包含了后续ZBuffer子类算法所需的protected保护继承变量
 *        
 *        所有子类必须实现scan，以进行扫描转化多边形物体
 */
class ZBuffer {
    protected:
        //屏幕宽度与高度
        int width, height;
        //待显示的多边形
        std::vector<Polygon> polygons;
        //视点朝向
        Eigen::RowVector3d eyeDir=Eigen::RowVector3d(0.0, 0.0, 1.0);
        //光源位置
        Eigen::RowVector3d light=Eigen::RowVector3d(0.0, 0.0, 1.0); 
        //物体颜色
        Eigen::RowVector3d color=Eigen::RowVector3d(1.0, 1.0, 0.0);
    public:
        //待显示的像素矩阵
        Eigen::MatrixXd pixelMat;
        ZBuffer(int width, int height,Model model);        
        virtual ~ZBuffer();
        //扫描转换
        virtual void scan()=0;
        //设置pixel颜色
        void setPixelcolor(Pixel pixel);
        
        void setPixelcolor(int x,int y,Eigen::RowVector3d color);
        //获取对应pixel的深度值
        // double getPixelz(Pixel pixel);
        std::vector<Pixel> calculatePixels(Polygon &polygon, int minX, int maxX, int minY, int maxY);
};

#endif