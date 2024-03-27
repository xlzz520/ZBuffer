#include "QuadZbuffer.h"

//非递归结构的zbuffer

QuadZbuffer::QuadZbuffer(int width, int height,ZBuffer* zbuffer)
{
    this->width=width;
    this->height=height;
    this->zbuffer=zbuffer;
	int w_temp = width;
	// 分配层次zbuffer的内存
    // 循环不断缩小zbuffer大小
	while (w_temp >= 1)
	{
		float* zbuffer = (float*)malloc(w_temp * w_temp * sizeof(float));
		zbuffers_.push_back(zbuffer);
		zbuffer_len_.push_back(w_temp);
		w_temp /= 2;
	}
}

QuadZbuffer::~QuadZbuffer()
{
	for (int i = 0; i < zbuffers_.size(); ++i)
	{
		free(zbuffers_[i]);
	}
}

// 得到二维平面的三角形的所在zbuffer树的层数和坐标, 最低为0层
int QuadZbuffer::getHeight(int x_max, int x_min, int y_max, int y_min, int &x, int &y)
{
	int height_x = 0, height_y = 0;
	while (x_max != x_min)
	{
		x_max /= 2;
		x_min /= 2;
		height_x++;
	}
	while (y_max != y_min)
	{
		y_max /= 2;
		y_min /= 2;
		height_y++;
	}
	x = x_max;
	y = y_max;

	int height = 0;
	if (height_x > height_y)
	{
		height = height_x;
		for (int i = 0; i < height - height_y; ++i)
		{
			y /= 2;
		}
	}
	else
	{
		height = height_y;
		for (int i = 0; i < height - height_x; ++i)
		{
			x /= 2;
		}
	}
	return height;
}


void QuadZbuffer::scanPolygon(Polygon &polygon)
{
    // 多边形极值
	int x_max = polygon.getX(), x_min = polygon.getX()-polygon.getDeltaX();
    int y_max = polygon.getY(), y_min = polygon.getY()-polygon.getDeltaY();
	float z_max =polygon.getZ();

	// 快速拒绝--如果多边形距离视点的z小于层次zbuffer树中的z，那么不被绘制
    if(!DepthTest(x_max,x_min,y_max,y_min, z_max)) return;
	
    //未能快速拒绝，需要进行寻常绘制绘制
    std::vector<Pixel> pixels = zbuffer->calculatePixels(polygon, 0, width-1, 0, height-1);
    addPixels(pixels);
}

bool QuadZbuffer::DepthTest(int x_max, int x_min, int y_max, int y_min, float z){
    int x, y;
	int height = getHeight(x_max - 1, x_min + 1, y_max - 1, y_min + 1, x, y);	// +1, -1防止在边界上

    //快速拒绝
    if (zbuffers_[height][y * zbuffer_len_[height] + x] <z)
        return true;
    else 
        return false;

}

void QuadZbuffer::scanOctree(OctreeNode *octreeNode) {

    // 八叉树极值
    AABB aabb=octreeNode->getAABB();
    int x_max = aabb.getMaxX(), x_min = aabb.getMinX();
    int y_max = aabb.getMaxY(), y_min = aabb.getMinY();

    //快速拒绝
    if(!DepthTest(x_max,x_min,y_max,y_min, octreeNode->getZ())) return;

    std::vector<Polygon> polygons = octreeNode->getPolygons();
    //绘制当前八叉树节点包含的多边形（一定不被子节点所包含）
    for (Polygon &polygon : polygons) {
        if (polygon.getDeltaX() > 0 && polygon.getDeltaY() >0) {
            std::vector<Pixel> pixels = zbuffer->calculatePixels(polygon, 0, width-1, 0, height-1);
            addPixels(pixels);
        }
    }

    //遍历八叉树子树继续进行绘制
    std::vector<OctreeNode *> octreeChildren = octreeNode->getChildren();
    for (OctreeNode *octreeChild : octreeChildren)
                scanOctree(octreeChild);

}





static float zMin(float z1, float z2, float z3, float z4)
{	
	float zmin = FLT_MAX;
	zmin = std::min(zmin, z1);
	zmin = std::min(zmin, z2);
	zmin = std::min(zmin, z3);
	zmin = std::min(zmin, z4);
	return zmin;
}





// 重写，绘制像素的时候更新层次z-buffer
void QuadZbuffer::addPixels(std::vector<Pixel> &pixels)
{   
    for (Pixel &pixel : pixels){

		int x=pixel.getX(),y=pixel.getY();
		float z=pixel.getZ();
		
		if(zbuffers_[0][x + y * width] >=z ) return;


		zbuffer->setPixelcolor(x, y, pixel.getColor());

		//更新zbuffer，从低到高更新zbuffer
		//第0层，全分别率
		zbuffers_[0][x + y * width] = pixel.getZ();
		//第1层及以上
		for (int i = 1; i < zbuffers_.size(); ++i)
		{   
			if (x % 2 == 1) x--;
			if (y % 2 == 1) y--;
			zbuffers_[i][(y / 2) * zbuffer_len_[i] + x / 2] = zMin(
				zbuffers_[i - 1][y * zbuffer_len_[i - 1] + x],
				zbuffers_[i - 1][y * zbuffer_len_[i - 1]+ x + 1],
				zbuffers_[i - 1][(y + 1) * zbuffer_len_[i - 1]+ x],
				zbuffers_[i - 1][(y + 1) * zbuffer_len_[i - 1]+ x + 1]
			);
			x /= 2;
			y /= 2;
		}
	}

}

