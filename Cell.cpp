#include "Cell.h"
#include "Mineral.h"
#include <iostream>


Cell::Cell(int w, int h, int x, int y, Frame *fr) : width(w),
						    height(h),
						    x(x),
						    y(y),
						    frame(fr)
{

}

Cell::~Cell()
{
	frame = nullptr;
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

void Cell::setFrame(Frame *fr)
{
	frame = fr;
}


Frame *Cell::getFrame() const
{
	return frame;
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
	for(auto& m: minerals)
		m->setParent(nullptr);

	minerals.clear();
}


int Cell::mineralCount() const
{
	return minerals.size();
}

std::ostream& operator<<(std::ostream& ostr, Cell& c)
{
	ostr << "Cell at (" << c.x << "," <<c.y << "):" << std::endl;

	unsigned int idx;

	for(idx=0; idx<c.minerals.size(); ++idx)
		ostr << "[" << idx+1 << "] " << *c.minerals[idx];

	return ostr;
}
