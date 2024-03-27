#ifndef _MODEL_
#define _MODEL_

#include <spdlog/spdlog.h>
#include <igl/read_triangle_mesh.h>

/**
 * @brief 模型类，读取顶点和面片
 * 
 */
class Model {
    private:
        //顶点、面片原始数据及其数量
        Eigen::MatrixXd V;   //顶点数量*3  double
        Eigen::MatrixXi F;   //面片数量*3  int
        int numberOfVertices;
        int numberOfFacets;
    public:
        Model();
        Model(const std::string &path);
        ~Model();
        int getnumberOfVertices();
        int getnumberOfFacets();
        //将顶点坐标x,y,z值都归一化到[-1,1]，进行规范化
        void normalization();
        Eigen::MatrixXd& getV();  
        Eigen::MatrixXi& getF();
};

#endif