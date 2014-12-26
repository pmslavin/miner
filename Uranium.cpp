#include "Uranium.h"
#include "Ground.h"
#include "constants.h"
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


void Uranium::draw(Uint32 *pixels, int fog)
{
	const int cell_w = parent->getWidth();
	const int cell_h = parent->getHeight();
	const int w = parent->getGround()->getWidth();

	const unsigned char most = Colours::Uranium >> 16 & 0xFF;
	unsigned char mid = (Colours::Uranium >> 8 & 0xFF) * yield/76.0;
	const unsigned char least = Colours::Uranium & 0xFF;

	mid = (mid < Colours::Uranium_Dark_byte) ? Colours::Uranium_Dark_byte : mid;
	mid /= fog;

	const uint32_t cbytes = (0x00 << 24) + (most << 16) + (mid << 8) + least;

	for(int r=0; r<cell_h; ++r){
		for(int c=0; c<cell_w; ++c){
			pixels[r*w+c] = cbytes;
//			pixels[c+r*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
		}
	}
}


Uranium *Uranium::extract(int quant)
{
	if(quant > yield)
		quant = yield;

	yield -= quant;
	return new Uranium(quant);
}
