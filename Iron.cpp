#include "Iron.h"
#include "Ground.h"
#include <iostream>

const std::string Iron::name = "Iron";
const std::string Iron::symbol = "Fe";

Iron::Iron(int yield) : Mineral(yield)
{

}


Iron::~Iron()
{
//	std::cout << "Destructing " << name << " then... ";
}


const std::string Iron::getName() const
{
	return name;
}


const std::string Iron::getSymbol() const
{
	return symbol;
}


void Iron::draw(Uint32 *pixels)
{
	int cell_w = parent->getWidth();
	int cell_h = parent->getHeight();
	int w = parent->getGround()->getWidth();
	int h = parent->getGround()->getHeight();

//	pixels[0] += (0x00 << 24) + (yield << 16);
//	Iron ore 0xED7B4A

	int most = 0xE0 * yield/180.0;
	int mid = 0x47 * yield/180.0;
	int least = 0x14 * yield/180.0;

	for(int r=0; r<cell_h; ++r){
		for(int c=0; c<cell_w; ++c){
			pixels[c+r*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
		}
	}

/*
	pixels[0] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[1] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[2] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[3] += (0x00 << 24) + (most << 16) + (mid << 8) + least;

	pixels[0+1*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[1+1*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[2+1*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[3+1*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;

	pixels[0+2*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[1+2*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[2+2*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[3+2*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;

	pixels[0+3*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[1+3*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[2+3*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[3+3*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
*/
}
