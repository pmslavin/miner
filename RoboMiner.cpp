#include <iostream>
#include "Frame.h"
#include "RoboMiner.h"
#include "Mineral.h"
#include "Base.h"



RoboMiner::RoboMiner(int cy, int cx, Frame *fr) : cell_y(cy),
						  cell_x(cx),
						  frame(fr),
						  energy(1000),
						  destCell(nullptr),
						  max_cargo(100),
						  lastMinedOre(nullptr),
						  base(nullptr)
{
//	pixels = new uint32_t[4*4];
	setCell(frame->getGround()->getCell(cy, cx));
	setDestination(160, 128);
	setBase(frame->getSurface()->getBase());
}


RoboMiner::~RoboMiner()
{
//	delete pixels;
}


void RoboMiner::draw(uint32_t *pixels)
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


void RoboMiner::setCell(Cell& c)
{
	cell = &c;
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
	cell->clearMiner();
	if(!destcell->isDrilled())
		drill(cy, cx);
	cell = destcell;
	cell->hasMiner(this);
	cell_y = cy;
	cell_x = cx;
}


int RoboMiner::drill(int cy, int cx)
{
	Cell &c = frame->getGround()->getCell(cy, cx);
	c.setDrilled(true);

	return 0;
}


void RoboMiner::action()
{

	if(rand() % 512 < 48)
		scan();

	while(cell->mineralCount() > 0 && !isFull())
		mine();

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

	std::vector<Mineral *> *output = cell->extract(extract_quant);

/*	std::cout << "Mining (" << cell_y << "," << cell_x
		  << ") yields:" << std::endl;

	int idx = 1;
	for(auto& m: *output){
		std::cout << '\t' << "[" << idx++ << "] "
			  << m->getYield() << " units of "
			  << m->getName() << std::endl;
	}
*/
	process(*output);
	delete output;
}


void RoboMiner::process(std::vector<Mineral *>& ores)
{
	if(isFull())
		return;

	bool present = false;
	Mineral *inCargo = nullptr;

	for(auto& m: ores){
		for(auto& c: cargo){
			if(c->getName() == m->getName()){
				present = true;
				inCargo = c;
			}
		}
		if(!present)
			cargo.push_back(&(*m));
		else{
			inCargo->setYield(inCargo->getYield() + m->getYield());
			m->setYield(0);
		}
		present = false;
	}
/* Minerals not deleted here are now owned by the RM.
 * Erase their iter from the vector, but don't
 * destruct the Mineral itself.
 */
	Mineral *m;
	for(auto it = ores.begin(); it != ores.end(); ){
		m = *it;
		if(!m->getYield()){
//			std::cout << "Erasing from ores: " << m->getName() << std::endl;
			delete m;
			ores.erase(it);
		}else{
			it++;
		}
	}

//	std::cout << "ores emptied: " << ores->size() << std::endl;
//	listCargo();
	if(isFull()){
		std::cout << "Cargo Full: Returning to base..." << std::endl;
		listCargo();
		setLastMinedOre(cell_y, cell_x);
		setDestination(0, 128);
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
			base->deposit(cargo);
			emptyCargo();
		}
//		emptyCargo();
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
	int onboard = 0;

	for(auto& m: cargo)
		onboard += m->getYield();

	if(onboard > max_cargo)
		onboard = max_cargo;

	return max_cargo - onboard;
}


void RoboMiner::emptyCargo()
{
	Mineral *m = nullptr;
	for(auto it = cargo.begin(); it != cargo.end(); ){
		m = *it;
		delete m;
		cargo.erase(it);
	}

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
	std::cout << "[Cargo]" << std::endl;
	int idx = 1;
	for(auto& c: cargo){
		std::cout << '\t' << "[" << idx++ << "] "
			  << c->getName() << " : " << c->getYield()
			  << " units" << std::endl;
	}

}


void RoboMiner::scan()
{
	int radius = 8;
	int x_radius = radius, y_radius = radius;
	int xdist, ydist;


	Ground *g = frame->getGround();
	
	if(cell_x + x_radius > g->getCols())
		x_radius = g->getCols()-1-cell_x;
	else if(cell_x - x_radius < 0)
		x_radius = cell_x;

	if(cell_y + y_radius > g->getRows())
		y_radius = g->getRows()-1-cell_y;
	else if(cell_y - y_radius < 0)
		y_radius = cell_y;

	std::vector<Cell *> scope;

//	std::cout << "scan from (" << cell_y << "," << cell_x
//		  << ")" << std::endl;

	for(xdist=-x_radius; xdist<=x_radius; ++xdist){
		for(ydist=-y_radius; ydist<=y_radius; ++ydist){
			if((abs(ydist)+abs(xdist))>radius)
				continue;
			if(ydist==0 && xdist==0)
				continue;
			Cell& scan_cell = g->getCell(cell_y+ydist, cell_x+xdist);
			scope.push_back(&scan_cell);
		}
	}

//	std::cout << "\ty_r: " << y_radius << "  x_r: "
//		  << x_radius << "  tc: " << scope.size() << std::endl;

	for(auto& c: scope){
//		std::cout << "(" << c->getY() << ","
//			  << c->getX() << ")" << std::endl;
		c->setVisible(true);
	}

	

}
