#include "Frame.h"
#include "RoboMiner.h"
#include "Mineral.h"
#include "MineralStore.h"
#include "Base.h"

#include <iostream>
#include <algorithm>
#include <iterator>


RoboMiner::RoboMiner(int cy, int cx, Frame *fr) : cell_y(cy),
						  cell_x(cx),
						  frame(fr),
						  destCell(nullptr),
						  lastMinedOre(nullptr),
						  drillCell(nullptr),
						  energy(2000),
						  max_cargo(1000),
						  exploring(false),
						  ascending(false),
						  drillCount(0),
						  ascendCount(0)
{
	Cell *startCell = &(frame->getGround()->getCell(cy, cx));
	setCell(startCell);
	startCell->setDrilled(true);
	startCell->hasMiner(this);
//	setDestination(160, 128);
	setBase(frame->getSurface()->getBase()); 
}


RoboMiner::~RoboMiner()
{
}


void RoboMiner::draw(uint32_t *pixels) const
{
/*
 *	0101
 *	1R1G
 *	1R1G
 *	0101
 */

	int w = frame->getGround()->getWidth();

	pixels[0] = 0x00;
	pixels[1] = 0x00FFFFFF;
	pixels[2] = 0x00;
	pixels[3] = 0x00FFFFFF;

	pixels[0+1*w] = 0x00FFFFFF;
	pixels[1+1*w] = 0x00FF0000;
	pixels[2+1*w] = 0x00FFFFFF;
	pixels[3+1*w] = 0x0000FF00;

	pixels[0+2*w] =  0x00FFFFFF;
	pixels[1+2*w] =  0x00FF0000;
	pixels[2+2*w] = 0x00FFFFFF;
	pixels[3+2*w] = 0x0000FF00;

	pixels[0+3*w] = 0x00;
	pixels[1+3*w] = 0x00FFFFFF;
	pixels[2+3*w] = 0x00;
	pixels[3+3*w] = 0x00FFFFFF;
}


int RoboMiner::getX() const
{
	return cell_x;
}


int RoboMiner::getY() const
{
	return cell_y;
}


void RoboMiner::setCell(Cell *c)
{
	cell = c;
}


void RoboMiner::move(int cy, int cx)
{

	Ground *gr = frame->getGround();
	int maxCell_x = gr->getCols();
	int maxCell_y = gr->getRows();

	if(cx<0 || cx>=maxCell_x)
		return;

	if(cy<0 || cy>=maxCell_y)
		return;

/*	std::cout << "Moving from (" << cell_y << "," << cell_x << ")"
		  << " Cell(" << cell->getY() << "," << cell->getX() << ")"
		  << " to (" << cy << "," << cx << ") with max_y: "
		  <<  maxCell_y << " max_x: " << maxCell_x << std::endl;
*/
	Cell *destcell = &(gr->getCell(cy, cx));
	if(!destcell->isDrilled())
		drill(cy, cx);

	if(destcell->isDrilled()){
		cell->clearMiner();
		cell = destcell;
		cell->hasMiner(this);
		cell_y = cy;
		cell_x = cx;
		energy -= 1;
	}
}


int RoboMiner::drill(int cy, int cx)
{
	if(!drillCount){
		drillCell = &(frame->getGround()->getCell(cy, cx));
		drillCell->setDrilling(true);
		drillCount = 5;
//		std::cout << "Drilling (" << cy << "," << cx << ") "
//			  << std::flush;
		return drillCount;
	}else{
//		std::cout << drillCount << "... " << std::flush;
		--drillCount;
	}

	if(!drillCount){
//		std::cout << std::endl;
		drillCell->setDrilled(true);
		drillCell = nullptr;
	}

	return drillCount;
}


void RoboMiner::action()
{

//	if(rand() % 512 < 48)
//		scan();

//	std::cout << "E: " << energy << std::endl;

	if(ascending){
		ascend();
		return;
	}

	if(drillCell){
		--energy;
		drill(drillCell->getY(), drillCell->getX());
		return;
	}

	if(cell->mineralCount() > 0 && !isFull()){
		--energy;
		mine();
		return;
	}

	if(!destCell || exploring){
		energy -= 2;
		scan();
	}

	if(destCell){
		navigate();
	}else{
		int offset_x=0, offset_y=0;
		int roll = rand() % 512;

		if(roll >= 255){
			offset_y = (roll % 2) ? 1 : -1;
		}else{
			offset_x = (roll % 2) ? 1 : -1;
		}

/*		std::cout << "[action] off_x: " << offset_x << "  off_y: "
			  << offset_y << "  from roll: " << roll
			  << std::endl;
*/
		move(cell_y + offset_y, cell_x + offset_x);
	}

	
}


void RoboMiner::mine()
{
	if(!cell->mineralCount() || isFull())
		return;

	int extract_quant = 5;
	int remain = getRemainingSpace();

	if(remain < extract_quant)
		extract_quant = remain;

	MineralStore *output = cell->extract(extract_quant);

//	std::cout << "Mining (" << cell_y << "," << cell_x
//		  << ") yields:" << std::endl;

//	std::cout << *output;
	process(*output);
	delete output;
}


void RoboMiner::process(MineralStore& ores)
{
	if(isFull())
		return;

	cargo += ores;

	if(isFull()){
		std::cout << "Cargo Full: Returning to base ("
			  << base->getY() << "," << base->getX()
			  << ")..." << std::endl;
		listCargo();
		setLastMinedOre(cell_y, cell_x);
		setDestination(base->getY(), base->getX());
	}
}


void RoboMiner::setDestination(int cy, int cx)
{
	destCell = &(frame->getGround()->getCell(cy, cx));
}


void RoboMiner::setLastMinedOre(int cy, int cx)
{
	lastMinedOre = &(frame->getGround()->getCell(cy, cx));
}


void RoboMiner::navigate()
{
	int dest_y = destCell->getY();
	int dest_x = destCell->getX();

	int y_off = cell_y - dest_y;
	int x_off = cell_x - dest_x;

	int move_x = 0, move_y = 0;
	Ground *g = frame->getGround();
	Cell& up = g->getCell((cell_y-1 >= 0 ? cell_y-1 : 0), cell_x);
	Cell& down = g->getCell((cell_y+1 < g->getRows() ? cell_y+1 : g->getRows()-1), cell_x);
	Cell& right = g->getCell(cell_y, (cell_x+1 < g->getCols() ? cell_x+1 : g->getCols()-1));
	Cell& left = g->getCell(cell_y, (cell_x-1 >= 0 ? cell_x-1 : 0));

	if(y_off > 0){
		if(x_off > 0){
			if(left.isDrilled()){
				move_x = -1;
				goto done;
			}
		}else if(x_off < 0){
			if(right.isDrilled()){
				move_x = 1;
				goto done;
			}
		}
		move_y = -1;
	}else if(y_off < 0){
		if(x_off > 0){
			if(left.isDrilled()){
				move_x = -1;
				goto done;
			}
		}else if(x_off < 0){
			if(right.isDrilled()){
				move_x = 1;
				goto done;
			}
		}
		move_y = 1;
		
	}else if(x_off > 0){
		if(y_off > 0){
			if(up.isDrilled()){
				move_y = -1;
				goto done;
			}
		}else if(y_off < 0){
			if(down.isDrilled()){
				move_y = 1;
				goto done;
			}
		}
		move_x = -1;
	}else if(x_off < 0){
		if(y_off > 0){
			if(up.isDrilled()){
				move_y = -1;
				goto done;
			}
		}else if(y_off < 0){
			if(down.isDrilled()){
				move_y = 1;
				goto done;
			}
		}
		move_x = 1;
	}

done:
	move(cell_y + move_y, cell_x + move_x);
	
	if(dest_y == cell_y && dest_x == cell_x){
		destCell = nullptr;
		if(atBase()){
			ascending = true;
		}
		if(lastMinedOre){
			setDestination(lastMinedOre->getY(), lastMinedOre->getX());
			lastMinedOre = nullptr;
		}
	}
}


bool RoboMiner::isFull() const
{
	return (getRemainingSpace() == 0);
}


int RoboMiner::getRemainingSpace() const
{
	int onboard = cargo.size();

	if(onboard > max_cargo)
		onboard = max_cargo;

	return max_cargo - onboard;
}


void RoboMiner::emptyCargo()
{
	cargo.emptyStore();	
}


void RoboMiner::setBase(Base *b)
{
	base = b;
}


bool RoboMiner::atBase() const
{
	return (cell_y == base->getY() && cell_x == base->getX());
}


void RoboMiner::listCargo() const
{
	std::cout << cargo;
}


void RoboMiner::scan()
{
	int radius = 6;
	int up_radius = radius, down_radius = radius;
	int left_radius = radius, right_radius = radius;
	int xdist, ydist;

	Ground *g = frame->getGround();
	
	if(cell_x + right_radius >= g->getCols())
		right_radius = g->getCols()-1-cell_x;
	if(cell_x - left_radius < 0)
		left_radius = cell_x;

	if(cell_y + down_radius >= g->getRows())
		down_radius = g->getRows()-1-cell_y;
	if(cell_y - up_radius < 0)
		up_radius = cell_y;

	std::vector<Cell *> scope;

//	std::cout << "scan from (" << cell_y << "," << cell_x
//		  << ")" << std::endl;

	for(xdist=-left_radius; xdist<=right_radius; ++xdist){
		for(ydist=-up_radius; ydist<=down_radius; ++ydist){
			if((abs(ydist)+abs(xdist))>radius)
				continue;
			if(ydist==0 && xdist==0)
				continue;
			Cell& scan_cell = g->getCell(cell_y+ydist, cell_x+xdist);
			scope.push_back(&scan_cell);
		}
	}

/*	std::cout << "\ty_r: " << y_radius << "  x_r: "
		  << x_radius << "  tc: " << scope.size() << std::endl;
	for(auto& c: scope){
		c->setVisible(true);
		if(c->mineralCount()){
			mineralCells.push_back(c);
		}
	}
*/
	std::vector<const Cell *> mineralCells;
	std::copy_if(scope.cbegin(), scope.cend(), std::back_inserter(mineralCells), \
			[](Cell *c){ c->setVisible(true); return c->mineralCount(); });

	if(mineralCells.empty() && !destCell){
		int roll = rand() % 4;
		int x_off=0, y_off=0;
		switch(roll){
			case 0:	y_off = -up_radius;
				break;
			case 1: x_off = right_radius;
				break;
			case 2: y_off = down_radius;
				break;
			case 3: x_off = -left_radius;
				break;
		}
//		std::cout << "Exploring to: (" << cell_y+y_off
//			  << "," << cell_x+x_off << ")" << std::endl;
		setDestination(cell_y + y_off, cell_x + x_off);
		exploring = true;
	}else if(!mineralCells.empty() && !destCell){
		exploring = false;
		int roll = rand() % mineralCells.size();
		const Cell *const hasMinerals = mineralCells[roll];
		setDestination(hasMinerals->getY(), hasMinerals->getX());
	}

	

}


int RoboMiner::ascend()
{
	if(!ascendCount){
		ascendCount = 5;
		cell->clearMiner();
		base->ascend(*this);
		base->deposit(cargo);
		energy = 2000;
	}else{
		--ascendCount;
	}

	if(!ascendCount){
		ascending = false;
		base->descend();
		cell->hasMiner(this);
	}

	return ascendCount;
}
