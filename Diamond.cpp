#include "Diamond.h"
#include "Ground.h"
#include <iostream>

const std::string Diamond::name = "Diamond";
const std::string Diamond::symbol = "Fe";

Diamond::Diamond(int yield) : Mineral(yield)
{

}


Diamond::~Diamond()
{
//	std::cout << "Destructing " << name << " then... ";
}


const std::string Diamond::getName() const
{
	return name;
}


const std::string Diamond::getSymbol() const
{
	return symbol;
}


void Diamond::draw(Uint32 *pixels)
{
//	int cell_w = parent->getWidth();
//	int cell_h = parent->getHeight();
	int w = parent->getGround()->getWidth();

//	Diamond 0xE0E0E0;
//	0010
//	1110
//	0111
//	0100

	int most = 0xE0 * yield/256.0;
	int mid = 0xE0 * yield/256.0;
	int least = 0xE0 * yield/256.0;

/*	for(int r=0; r<cell_h; ++r){
		for(int c=0; c<cell_w; ++c){
			pixels[c+r*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
		}
	}
*/

	pixels[2] += (0x00 << 24) + (most << 16) + (mid << 8) + least;

	pixels[0+1*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[1+1*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[2+1*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;

	pixels[1+2*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[2+2*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
	pixels[3+2*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;

	pixels[1+3*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;

}


Diamond *Diamond::extract(int quant)
{
	if(quant > yield)
		quant = yield;

	yield -= quant;
	return new Diamond(quant);
}
