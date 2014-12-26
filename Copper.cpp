#include "Copper.h"
#include "Ground.h"
#include "constants.h"
#include <iostream>

const std::string Copper::name = "Copper";
const std::string Copper::symbol = "Cu";

Copper::Copper(int yield) : Mineral(yield)
{

}


Copper::~Copper()
{

}


const std::string Copper::getName() const
{
	return name;
}


const std::string Copper::getSymbol() const
{
	return symbol;
}


void Copper::draw(Uint32 *pixels, int fog)
{
	const int cell_w = parent->getWidth();
	const int cell_h = parent->getHeight();
	const int w = parent->getGround()->getWidth();

	const unsigned char most = (Colours::Copper>>16 & 0xFF) * yield/128.0 / fog;
	const unsigned char mid = (Colours::Copper>>8 & 0xFF) * yield/128.0 / fog;
	const unsigned char least = (Colours::Copper & 0xFF) * yield/128.0 / fog;

	const uint32_t cbytes = (0x00 << 24) + (most << 16) + (mid << 8) + least;

	for(int r=0; r<cell_h; ++r){
		for(int c=0; c<cell_w; ++c){
			pixels[r*w+c] = cbytes;
//			pixels[c+r*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
		}
	}

}


Copper *Copper::extract(int quant)
{
	if(quant > yield)
		quant = yield;

	yield -= quant;
	return new Copper(quant);
}
