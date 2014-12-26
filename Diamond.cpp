#include "Diamond.h"
#include "Ground.h"
#include <iostream>

const std::string Diamond::name = "Diamond";
const std::string Diamond::symbol = "Di";

Diamond::Diamond(int yield) : Mineral(yield)
{

}


Diamond::~Diamond()
{

}


const std::string Diamond::getName() const
{
	return name;
}


const std::string Diamond::getSymbol() const
{
	return symbol;
}


void Diamond::draw(Uint32 *pixels, int fog)
{
//	int cell_w = parent->getWidth();
//	int cell_h = parent->getHeight();
	int w = parent->getGround()->getWidth();

//	Diamond 0xE0E0E0;
//	0010
//	1110
//	0111
//	0100

	const unsigned char most = 0xF0 / fog;
	const unsigned char mid = 0xF0 / fog;
	const unsigned char least = 0xF0 / fog;
	const uint32_t cbytes = (0x00 << 24) + (most << 16) + (mid << 8) + least;

	pixels[2] = cbytes;

	pixels[0+1*w] = cbytes;
	pixels[1+1*w] = cbytes;
	pixels[2+1*w] = cbytes;

	pixels[1+2*w] = cbytes;
	pixels[2+2*w] = cbytes;
	pixels[3+2*w] = cbytes;

	pixels[1+3*w] = cbytes;
}


Diamond *Diamond::extract(int quant)
{
	if(quant > yield)
		quant = yield;

	yield -= quant;
	return new Diamond(quant);
}
