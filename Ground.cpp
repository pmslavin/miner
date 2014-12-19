#include "Ground.h"
#include "Iron.h"
#include "Copper.h"
#include "Gold.h"
#include "Diamond.h"


Ground::Ground(int w, int h, Frame *fr) : width(w), height(h), frame(fr)
{
	cell_rows = height/4;
	cell_cols = width/4;

	for(int i=0; i<cell_rows*cell_cols; ++i){
		cells.push_back(Cell(4, 4, i%cell_cols, i/cell_cols, this));
	}

	pixels = new Uint32[w*h];

	calcMinerals();
}


Ground::~Ground()
{
	delete [] pixels;
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
		if(rand() % 36 == 0)
			c.addMineral(new Iron(rand() % 180));

		if(rand() % 64 == 7 && c.getY() > cell_rows/4)
			c.addMineral(new Copper(rand() % 128));

		if(rand() % 128 == 77 && c.getY() > cell_rows/1.7)
			c.addMineral(new Gold(rand() % 96));

		if(rand() % 512 == 77 && c.getY() > cell_rows/1.3)
			c.addMineral(new Diamond(rand() % 256));
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


int Ground::getWidth() const
{
	return width;
}


int Ground::getHeight() const
{
	return height;
}


void Ground::clearCells()
{
	for(auto& c: cells)
		c.clearMinerals();	
}


void Ground::draw()
{
	
	memset(pixels, 0, width*height*sizeof(Uint32));

	for(auto& c: cells)
		c.drawMinerals(&pixels[width*c.getY()*c.getHeight()+c.getX()*c.getWidth()]);
}


const Uint32 *Ground::getPixels() const
{
	return pixels;
}
