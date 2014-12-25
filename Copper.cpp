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
//	std::cout << "Destructing " << name << " then... ";
}


const std::string Copper::getName() const
{
	return name;
}


const std::string Copper::getSymbol() const
{
	return symbol;
}


void Copper::draw(Uint32 *pixels)
{
	int cell_w = parent->getWidth();
	int cell_h = parent->getHeight();
	int w = parent->getGround()->getWidth();

//        pixels[y*w+x] = 0x00E89149;
//        pixels[0] += 0x00E89149*yield/768.0;
//	Copper ore 0x0EAD88;

	const unsigned char most = (Colours::Copper>>16 & 0xFF) * yield/128.0;
	const unsigned char mid = (Colours::Copper>>8 & 0xFF) * yield/128.0;
	const unsigned char least = (Colours::Copper & 0xFF) * yield/128.0;

	for(int r=0; r<cell_h; ++r){
		for(int c=0; c<cell_w; ++c){
			pixels[c+r*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
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
