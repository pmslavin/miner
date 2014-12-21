#include "Uranium.h"
#include "Ground.h"
#include <iostream>

const std::string Uranium::name = "Uranium";
const std::string Uranium::symbol = "U";

Uranium::Uranium(int yield) : Mineral(yield)
{

}


Uranium::~Uranium()
{
//	std::cout << "Destructing " << name << " then... ";
}


const std::string Uranium::getName() const
{
	return name;
}


const std::string Uranium::getSymbol() const
{
	return symbol;
}


void Uranium::draw(Uint32 *pixels)
{
	int cell_w = parent->getWidth();
	int cell_h = parent->getHeight();
	int w = parent->getGround()->getWidth();

//	pixels[0] += (0x00 << 24) + (yield << 16);
//	Iron ore 0xED7B4A

/*	int most = 0xE0 * yield/180.0;
	int mid = 0x47 * yield/180.0;
	int least = 0x14 * yield/180.0;
*/

	int most = 0x00;
	int mid = 0xFF * yield/76.0;
	int least = 0x00;

	mid = (mid < 0xA7) ? 0xA7 : mid;

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


Uranium *Uranium::extract(int quant)
{
	if(quant > yield)
		quant = yield;

	yield -= quant;
	return new Uranium(quant);
}