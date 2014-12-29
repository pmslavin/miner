#include "Iron.h"
#include "Ground.h"
#include "constants.h"
#include <iostream>

const std::string Iron::name = "Iron";
const std::string Iron::symbol = "Fe";

Iron::Iron(int yield) : Mineral(yield)
{

}


Iron::~Iron()
{

}


const std::string Iron::getName() const
{
	return name;
}


const std::string Iron::getSymbol() const
{
	return symbol;
}


void Iron::draw(Uint32 *pixels, int fog)
{
	int cell_w = parent->getWidth();
	int cell_h = parent->getHeight();
	int w = parent->getGround()->getWidth();

	const unsigned char most = (Colours::Iron>>16 & 0xFF) * yield/180.0/fog;
	const unsigned char mid = (Colours::Iron>>8 & 0xFF) * yield/180.0/fog;
	const unsigned char least = (Colours::Iron & 0xFF) * yield/180.0/fog;

	const uint32_t cbytes = (0x00 << 24) + (most << 16) + (mid << 8) + least;

	for(int r=0; r<cell_h; ++r){
		for(int c=0; c<cell_w; ++c){
			pixels[r*w+c] += cbytes;
//			pixels[c+r*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
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


Iron *Iron::extract(int quant)
{
	if(quant > yield)
		quant = yield;

	yield -= quant;

	return new Iron(quant);
}
