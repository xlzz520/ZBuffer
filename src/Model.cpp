#include "Model.h"
 
Model::Model(const std::string &path){ 
    igl::read_triangle_mesh(path, V, F); 
    spdlog::info("read obj file with {} vertex, {} triangle", V.rows(), F.rows());
    numberOfVertices=V.rows();
    numberOfFacets=F.rows();
    normalization();
}
Model::~Model(){}

void Model::normalization(){
    

    //归一化:x,y,z∈(-1/2,1/2)
    V = V / (V.maxCoeff() - V.minCoeff());    
    Eigen::RowVector3d center = (V.colwise().minCoeff() + V.colwise().maxCoeff()) / 2.0;    //求最小包络盒的中心(x,y,z)
    
    //TODO加速

    #pragma omp parallel for
    for(int vI=0; vI<V.rows(); ++vI){
        V.row(vI) -= center;
    }
}
int Model::getnumberOfVertices(){
    return numberOfVertices;
}
int Model::getnumberOfFacets(){
    return numberOfFacets;
}
Eigen::MatrixXd& Model::getV(){
    return V;
} 
Eigen::MatrixXi& Model::getF(){
    return F;
}