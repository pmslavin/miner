#include "Copper.h"
#include "Ground.h"
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

	int most = 0x0E * yield/128.0;
	int mid = 0xAD * yield/128.0;
	int least = 0x88 * yield/128.0;

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
