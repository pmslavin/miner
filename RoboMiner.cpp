#include <iostream>
#include "Frame.h"
#include "RoboMiner.h"



RoboMiner::RoboMiner(int cx, int cy, Frame *fr) : cell_x(cx),
	  					  cell_y(cy),
						  frame(fr),
						  energy(2000)
{
//	pixels = new uint32_t[4*4];
	setCell(&(frame->getGround()->getCell(cx, cy)));
	
}


RoboMiner::~RoboMiner()
{
//	delete pixels;
}


const uint32_t *RoboMiner::getPixels() const
{
//	return pixels;
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


void RoboMiner::setCell(Cell *c)
{
	cell = c;
}


void RoboMiner::move(int cx, int cy)
{
	int maxCell_x = frame->getGround()->getCols();
	int maxCell_y = frame->getGround()->getRows();

	if(cx<0 || cx>maxCell_x)
		return;

	if(cy<0 || cy>maxCell_y)
		return;

	std::cout << "Moving from (" << cell_x << "," << cell_y << ")"
		  << "to (" << cx << "," << cy << ")" << std::endl;

	Cell *destcell = &(frame->getGround()->getCell(cx, cy));
	cell->clearMiner();
	cell = destcell;
	cell->hasMiner(this);
	cell_x = cx;
	cell_y = cy;
}


int RoboMiner::drill(int cx, int cy)
{
	return 0;
}


void RoboMiner::action()
{

	if(rand() % 512 >= 77)
		return;

	int offset_x=0, offset_y=0;
	int roll = rand() % 512;

	if(roll >= 255){
		offset_x = (roll % 2) ? 1 : -1;
	}else{
		offset_y = (roll % 2) ? 1 : -1;
	}

/*	std::cout << "[action] off_x: " << offset_x << "  off_y: "
		  << offset_y << "  from roll: " << roll
		  << std::endl;
*/
	move(cell_x + offset_x, cell_y + offset_y);
}
