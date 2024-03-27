#include  "SimpleHiz.h"

SimpleHiz::SimpleHiz(int width, int height,Model model) : ZBuffer(width,height,model) {}

SimpleHiz::~SimpleHiz() {}

void SimpleHiz::scan(){
    //建立层次zbuffer
    hizbuffer=new QuadTree(width,height,this);
    QuadTreeNode* root=hizbuffer->Getroot();
    //每个多边形进行扫描
    for (Polygon polygon:polygons)
    {       
        //多边形不能是线段
        if (polygon.getDeltaX() > 0 && polygon.getDeltaY() >0) {
            root->scanPolygon(polygon);
        }
    }
}
