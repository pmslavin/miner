#include "Cell.h"
#include "Mineral.h"
#include "Ground.h"
#include "RoboMiner.h"
#include "constants.h"
#include "MineralStore.h"
#include <iostream>


Cell::Cell(int w, int h, int x, int y, Ground *g) : width(w),
						    height(h),
						    x(x),
						    y(y),
						    ground(g),
						    miner(nullptr),
						    visible(false),
						    drilling(false),
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
	int fog = 1;

	if(!isVisible())
		fog = 4;
	
	if(!minerals.empty())
		drawBlank(pixels);
	else if(drilling)
		drawDrillProgress(pixels);
	else if(!isDrilled())
		drawDepthShade(pixels, fog);	
	else if(isDrilled())
		drawDrilled(pixels);

	for(auto& m: minerals)
		m->draw(pixels, fog);

	if(miner)
		miner->draw(pixels);
}


void Cell::drawDrilled(Uint32 *pixels)
{
	const int w = ground->getWidth();
	const int cell_w = getWidth();
	const int cell_h = getHeight();

	for(int r=0; r<cell_h; ++r){
		for(int c=0; c<cell_w; ++c){
			pixels[r*w+c] = (r+c) % 2 ?
					Colours::Cell::Drilled::Dark : Colours::Cell::Drilled::Light;
		}
	}
}


void Cell::drawDrillProgress(Uint32 *pixels)
{
	const int w = ground->getWidth();
	const int cell_w = getWidth();
	const int cell_h = getHeight();

	for(int r=0; r<cell_h; ++r){
		for(int c=0; c<cell_w; ++c){
			pixels[r*w+c] = (r+c) % 2 ?
					Colours::Cell::Drilled::Dark : Colours::Yellow;
		}
	}
}


void Cell::drawBlank(Uint32 *pixels)
{
	const int w = ground->getWidth();
	const int cell_w = getWidth();
	const int cell_h = getHeight();

	for(int r=0; r<cell_h; ++r){
		for(int c=0; c<cell_w; ++c){
			pixels[r*w+c] = Colours::Black;
		}
	}
}


void Cell::drawDepthShade(Uint32 *pixels, int fog)
{
	const int grh = ground->getHeight();
	const int grw = ground->getWidth();
	const int cell_w = getWidth();
	const int cell_h = getHeight();
	int depth = getY()*cell_h;
	depth = depth>grh ? grh : depth;

/*	unsigned const char most_d = (Colours::Cell::Empty::Dark>>16 & 0xFF)/fog;
	unsigned const char mid_d = (Colours::Cell::Empty::Dark>>8 & 0xFF)/fog;
	unsigned const char least_d = (Colours::Cell::Empty::Dark & 0xFF)/fog;
*/
	unsigned const char most_l = (Colours::Cell::Empty::Light>>16 & 0xFF)/fog;
	unsigned const char mid_l = (Colours::Cell::Empty::Light>>8 & 0xFF)/fog;
	unsigned const char least_l = (Colours::Cell::Empty::Light & 0xFF)/fog;

	for(int r=0; r<cell_h; r+=2){
		for(int c=0; c<cell_w; ++c){
/*			pixels[r*grw+c] = (0x00<<24) + (most_d*(grh-depth-r)/grh << 16)
						     + (mid_d*(grh-depth-r)/grh  << 8)
						     + least_d;
*/			pixels[(r+1)*grw+c] = (0x00<<24) + (most_l*(grh-depth-r)/grh << 16)
						         + (mid_l*(grh-depth-r)/grh  << 8)
	 					         + least_l;
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


void Cell::setDrilling(bool isdrilling)
{
	drilling = isdrilling;
}

void Cell::setDrilled(bool isdrilled)
{
	drilled = isdrilled;
	drilling = false;
	setVisible(true);
}


bool Cell::isDrilled() const
{
	return drilled;
}


MineralStore *Cell::extract(int quant)
{
	MineralStore *ores = new MineralStore();

	for(auto& m: minerals){
		*ores += *(m->extract(quant));
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
	return ores;
}


int Cell::distanceFrom(const Cell& c) const
{
	int xmoves = abs(getX() - c.getX());
	int ymoves = abs(getY() - c.getY());

	return xmoves + ymoves;
}
