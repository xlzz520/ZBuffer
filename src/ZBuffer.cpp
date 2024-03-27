#include "ZBuffer.h"
#include "Utils.h"

ZBuffer::ZBuffer(int width, int height, Model model) {
    this->width = width;
    this->height = height;
    int numberOfFacets=model.getnumberOfFacets();
    
    //TODO 加速
    
    #pragma omp parallel for
    //建立多边形表
    for(int i=0; i<numberOfFacets; ++i)
    {   
        //第i个面片对应节点序号
        Eigen::RowVector3i v_index=model.getF().row(i);
        
        std::vector<Vertex> polygonVertices;
        for (int j = 0; j < 3; j++)
            polygonVertices.push_back( Vertex( model.getV()(v_index[j],Eigen::all) ));
        Polygon polygon(polygonVertices, width, height);
        // 简单的Flat shading
        //光源到三角形平均点 为照射方向
        Eigen::RowVector3d lightDir = (light - model.getV()(model.getF().row(i),Eigen::all).colwise().mean());
        lightDir.normalize();   
        Eigen::RowVector3d normal = (polygonVertices[1].position-polygonVertices[0].position).cross(polygonVertices[2].position-polygonVertices[0].position);
        normal.normalize();
        double factor = abs(normal.dot(lightDir));
        polygon.SetColor(color*factor);
        polygons.push_back(polygon);
    }

    pixelMat.setZero(height, width*3);
}

ZBuffer::~ZBuffer() {}


void ZBuffer::setPixelcolor(Pixel pixel){
    pixelMat(pixel.getY(),Eigen::seqN(pixel.getX()*3, Eigen::fix<3>))=pixel.getColor()({0, 1, 2});  

    // pixelMat(pixel.getX(),Eigen::seqN(pixel.getY()*3, Eigen::fix<3>))=pixel.getColor()({0, 1, 2});  
}

void ZBuffer::setPixelcolor(int x,int y,Eigen::RowVector3d color){
    pixelMat(y,Eigen::seqN(x*3, Eigen::fix<3>))=color({0, 1, 2});
}

std::vector<Pixel> ZBuffer::calculatePixels(Polygon &polygon, int minX, int maxX, int minY, int maxY) {
    std::vector<Pixel> ans;
    ActivePolygon activePolygon(polygon);
    //从上到下进行扫描
    int startY=polygon.getY();
    int endY=polygon.getY() - polygon.getDeltaY();

    for (int scanlineY = startY; scanlineY >= endY && scanlineY >= minY; scanlineY--) {
        activePolygon.check(scanlineY);
        if (scanlineY <= maxY) {
            Segment segment = activePolygon.segment();
            int startX=segment.getX(),endX=segment.getX()+segment.getDeltaX();
            double dz=segment.getDz();
            float z=segment.getZ();
            for (int scanlineX = startX; scanlineX <= endX&& scanlineX <= maxX; scanlineX++) {
                if (scanlineX >= minX) {
                    ans.push_back(Pixel(scanlineX, scanlineY, z, polygon.getColor()));
                    z+=dz;
                }
            }
        }
        activePolygon.update();
    }

    return ans;
}