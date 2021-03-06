#include "Ground.h"
#include "Iron.h"
#include "Copper.h"
#include "Gold.h"
#include "Diamond.h"
#include "Uranium.h"

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cstring>

#include "SDL2/SDL.h"


Ground::Ground(int w, int h, Frame *fr) : width(w), height(h), frame(fr)
{
	cell_rows = height/CELL_SZ;
	cell_cols = width/CELL_SZ;

	cells.reserve(cell_rows*cell_cols);
	for(int i=0; i<cell_rows*cell_cols; ++i){
		cells.push_back(Cell(CELL_SZ, CELL_SZ, i%cell_cols, i/cell_cols, this));
	}

	surf = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	pixels = static_cast<Uint32 *>(surf->pixels);
//	pixels = new Uint32[width*height];
	std::memset(pixels, 0, width*height*sizeof(Uint32));
	calcMinerals();
}


Ground::~Ground()
{
	delete [] pixels;
}


Cell& Ground::getCell(int y, int x)
{
	if((x < 0 || x >= cell_cols) || (y < 0 || y >= cell_rows)){
		std::ostringstream ess;
		ess << "Invalid Cell: getCell(" << y << ","
			  << x << ")";
		throw std::out_of_range(ess.str());
	}
	return cells[y*cell_cols + x]; 
}


void Ground::calcMinerals()
{
	for(auto& c: cells){
		if(rand() % 36 == 0)
			c.addMineral(new Iron(rand() % 180 + 1));

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
	for(auto& c: cells)
		c.drawMinerals(&pixels[width*c.getY()*c.getHeight()+c.getX()*c.getWidth()]);
	
}


const Uint32 *Ground::getPixels() const
{
	return pixels;
}


SDL_Surface *Ground::getSurf() const
{
	return surf;
}
