#include "Cell.h"
#include "Mineral.h"
#include "Ground.h"
#include "RoboMiner.h"
#include <iostream>
#include <algorithm>


Cell::Cell(int w, int h, int x, int y, Ground *g) : width(w),
						    height(h),
						    x(x),
						    y(y),
						    ground(g),
						    miner(nullptr),
						    visible(false),
						    drilled(false)
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

//	if(isDrilled())
	if(isDrilled() && minerals.empty())
		drawDrilled(pixels);

	for(auto& m: minerals)
		m->draw(pixels);

	if(miner)
		miner->draw(pixels);
}


void Cell::drawDrilled(Uint32 *pixels)
{
	int w = ground->getWidth();
	int cell_w = getWidth();
	int cell_h = getHeight();

	for(int r=0; r<cell_h; ++r){
		for(int c=0; c<cell_w; ++c){
			pixels[r*w+c] = (r+c) % 2 ? 0x006A6A6A : 0x00818582;
//			pixels[r*w+c] = 0x008C918E;
//			pixels[r*w+c] = 0x009DA39F;
		}
	}
}


void Cell::hasMiner(RoboMiner *rm)
{
	miner = rm;
}


void Cell::clearMiner()
{
	miner = nullptr;
}


void Cell::setVisible(bool isvis)
{
	visible = isvis;
}


bool Cell::isVisible() const
{
	return visible;
}


void Cell::setDrilled(bool isdrilled)
{
	drilled = isdrilled;
}


bool Cell::isDrilled() const
{
	return drilled;
}


std::vector<Mineral *> *Cell::extract(int quant)
{
	std::vector<Mineral *> *ores = new std::vector<Mineral *>;

	for(auto& m: minerals){
		ores->push_back(m->extract(quant));
	}

	Mineral *m;
	for(auto it = minerals.begin(); it != minerals.end(); ){
		m = *it;
		if(!m->getYield()){
//			std::cout << "Erasing " << m->getName() << "("
//				  << y << "," << x << ")" << std::endl;
			delete m;
			minerals.erase(it);
		}else{
			it++;
		}
	}
//	minerals.erase(std::remove_if(std::begin(minerals), std::end(minerals), isEmpty), std::end(minerals)); 
	return ores;
}


