#include "Cell.h"
#include "Mineral.h"
#include <iostream>


Cell::Cell(int w, int h, int x, int y, Ground *g) : width(w),
						    height(h),
						    x(x),
						    y(y),
						    ground(g)
{

}

Cell::~Cell()
{
	ground = nullptr;
}


int Cell::getWidth() const
{
	return width;
}


int Cell::getHeight() const
{
	return height;
}


int Cell::getX() const
{
	return x;
}


int Cell::getY() const
{
	return y;
}


void Cell::setGround(Ground *g)
{
	ground = g;
}


Ground *Cell::getGround() const
{
	return ground;
}


void Cell::addMineral(Mineral *m)
{
	m->setParent(this);
	minerals.push_back(m);
}


void Cell::clearMinerals()
{
//	for(auto iter=minerals.begin(); iter != minerals.end(); ++iter){
//		(*iter)->setParent(nullptr);
//	}
	for(auto& m: minerals){
		m->setParent(nullptr);
		delete m;
	}

	minerals.clear();
}


int Cell::mineralCount() const
{
	return minerals.size();
}

std::ostream& operator<<(std::ostream& ostr, Cell& c)
{
	ostr << "Cell at (" << c.y << "," << c.x << "):" << std::endl;

	unsigned int idx;

	for(idx=0; idx<c.minerals.size(); ++idx)
		ostr << "[" << idx+1 << "] " << *c.minerals[idx];

	return ostr;
}


void Cell::drawMinerals(Uint32 *pixels)
{
	for(auto& m: minerals){
		m->draw(pixels);
	}
}
