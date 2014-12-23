#include "Ground.h"
#include "Iron.h"
#include "Copper.h"
#include "Gold.h"
#include "Diamond.h"
#include "Uranium.h"
#include <iostream>


Ground::Ground(int w, int h, Frame *fr) : width(w), height(h), frame(fr)
{
	cell_rows = height/4;
	cell_cols = width/4;

	for(int i=0; i<cell_rows*cell_cols; ++i){
		cells.push_back(Cell(4, 4, i%cell_cols, i/cell_cols, this));
	}

	pixels = new Uint32[width*height];
	memset(pixels, 0, width*height*sizeof(Uint32));

/*	int most = 0x2E;
	int mid = 0x13;
	int least = 0x00;

	for(int r=0; r<h; ++r){
		for(int c=0; c<w; ++c){
			pixels[r*w+c] = (0x00<<24) + (most*(h-r)/h << 16) + (mid*(h-r)/h << 8) + least*(h-r)/h;
		}
	}
*/
	calcMinerals();
}


Ground::~Ground()
{
	delete [] pixels;
}


Cell& Ground::getCell(int y, int x)
{
	if((x < 0 || x >= cell_cols) || (y < 0 || y >= cell_rows)){
		std::cerr << "G->getCell() error: (" << y << ","
			  << x << ")" << std::endl;
		throw std::exception();
	}
	return cells[y*cell_cols + x]; 
}


void Ground::calcMinerals()
{
	for(auto& c: cells){
		if(rand() % 36 == 0)
			c.addMineral(new Iron(rand() % 180 + 1));
//			c.addMineral(new Iron(5));

		if(rand() % 64 == 7 && c.getY() > cell_rows/6)
			c.addMineral(new Copper(rand() % 128 + 1));

		if(rand() % 128 == 77 && c.getY() > cell_rows/2)
			c.addMineral(new Gold(rand() % 96 + 1));

		if(rand() % 256 == 77 && c.getY() > cell_rows/1.8)
			c.addMineral(new Uranium(rand() % 76 + 1));

		if(rand() % 400 == 77 && c.getY() > cell_rows/1.4)
			c.addMineral(new Diamond(rand() % 256 + 1));
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
	
//	memset(pixels, 0, width*height*sizeof(Uint32));
/*	int most = 0x2E;
	int mid = 0x13;
	int least = 0x00;

	for(int r=0; r<height; ++r){
		for(int c=0; c<width; ++c){
			pixels[r*width+c] = (0x00<<24)  + (most*(height-r)/height << 16)
							+ (mid*(height-r)/height << 8)
							+ least*(height-r)/height;
		}
	}
*/
	for(auto& c: cells)
		c.drawMinerals(&pixels[width*c.getY()*c.getHeight()+c.getX()*c.getWidth()]);
}


const Uint32 *Ground::getPixels() const
{
	return pixels;
}
