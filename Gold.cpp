#include "Gold.h"
#include "Ground.h"
#include "constants.h"
#include <iostream>

const std::string Gold::name = "Gold";
const std::string Gold::symbol = "Au";

Gold::Gold(int yield) : Mineral(yield)
{

}


Gold::~Gold()
{

}


const std::string Gold::getName() const
{
	return name;
}


const std::string Gold::getSymbol() const
{
	return symbol;
}


void Gold::draw(Uint32 *pixels, int fog)
{
	int cell_w = parent->getWidth();
	int cell_h = parent->getHeight();
	int w = parent->getGround()->getWidth();

//	pixels[0] += (0x00 << 24) + (yield << 16);
//	Gold ore 0xF0D000

	const unsigned char most = (Colours::Gold>>16 & 0xFF) * yield/96.0 / fog;
	const unsigned char mid = (Colours::Gold>>8 & 0xFF) * yield/96.0 / fog;
	const unsigned char least = (Colours::Gold & 0xFF) * yield/96.0 / fog;

	const uint32_t cbytes = (0x00 << 24) + (most << 16) + (mid << 8) + least;

	for(int r=0; r<cell_h; ++r){
		for(int c=0; c<cell_w; ++c){
			pixels[r*w+c] = cbytes;
//			pixels[c+r*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
		}
	}
}


Gold *Gold::extract(int quant)
{
	if(quant > yield)
		quant = yield;

	yield -= quant;

	return new Gold(quant);
}
