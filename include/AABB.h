#ifndef _AABB_
#define _AABB_

#include "Polygon.h"

/**
 * @brief 包围盒
 * 
 */

class AABB
{
	private:
		int minX, maxX, minY, maxY;
		float minZ, maxZ;
	public:
		AABB(int _minX, int _maxX, int _minY, int _maxY, float _minZ, float _maxZ);
		AABB(int _minX, int _maxX, int _minY, int _maxY);
		AABB();
		int getMinX();
		int getMaxX();
		int getMinY();
		int getMaxY();
		float getMinZ();
		float getMaxZ();
		//包含测试
		bool contain(int x,int y,float z);
		bool contain(int x,int y);
		bool contain(Polygon polygon);
		bool contain(AABB aabb);
		bool contain(int xmin,int xmax,int ymin,int ymax );
};
#endif