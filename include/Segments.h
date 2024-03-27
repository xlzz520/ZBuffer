#ifndef _SEGMENT_
#define _SEGMENT_

#include<Eigen/Eigen>
/**
 * @brief 扫描线片段类
 *        记录了扫描线片段的左端点的x与z，以及从左端点到右端点的dz和长度deltaX
 */
class Segment {
    private:
        //左端点的x、z和p值，右端点减去左端点的deltaX、dz和dp值
        int x, deltaX;
        float z, dz;
        Eigen::RowVector3d color;
        
    public:
        Segment(int x, int deltaX, float z, float dz, Eigen::RowVector3d color);
        ~Segment();
        int getX();
        int getDeltaX();
        float getZ();
        float getDz();
        Eigen::RowVector3d getColor();
};

#endif