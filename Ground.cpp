#include "Ground.h"
#include "Iron.h"
#include "Copper.h"


Ground::Ground(int w, int h, Frame *fr) : width(w), height(h), frame(fr)
{
	cell_rows = height/4;
	cell_cols = width/4;

	for(int i=0; i<cell_rows*cell_cols; ++i){
		cells.push_back(Cell(4, 4, i%cell_cols, i/cell_cols, this));
	}
}


Ground::~Ground()
{

}


Cell& Ground::getCell(int y, int x)
{
	if((x < 0 || x >= cell_cols) || (y < 0 || y >= cell_rows)){
		throw std::exception();
	}
	return cells[y*cell_cols + x]; 
}


void Ground::calcMinerals()
{
	for(auto& c: cells){
		if(rand() % 16 == 0)
			c.addMineral(new Iron(rand() % 180));

		if(rand() % 24 == 7)
			c.addMineral(new Copper(rand() % 120));
	}
}


int Ground::getRows() const
{
	return cell_rows;
}


int Ground::getCols() const
{
	return cell_cols;
}


void Ground::clearCells()
{
	for(auto& c: cells)
		c.clearMinerals();	
}



void Ground::draw(Uint32 *pixels)
{
	for(auto& c: cells)
		c.drawMinerals(&pixels[width*c.getY()*c.getHeight()+c.getX()*c.getWidth()]);
}
