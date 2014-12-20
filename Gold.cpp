#include "Gold.h"
#include "Ground.h"
#include <iostream>

const std::string Gold::name = "Gold";
const std::string Gold::symbol = "Fe";

Gold::Gold(int yield) : Mineral(yield)
{

}


Gold::~Gold()
{
//	std::cout << "Destructing " << name << " then... ";
}


const std::string Gold::getName() const
{
	return name;
}


const std::string Gold::getSymbol() const
{
	return symbol;
}


void Gold::draw(Uint32 *pixels)
{
	int cell_w = parent->getWidth();
	int cell_h = parent->getHeight();
	int w = parent->getGround()->getWidth();

//	pixels[0] += (0x00 << 24) + (yield << 16);
//	Gold ore 0xF0D000

	int most = 0xF0 * yield/96.0;
	int mid = 0xD0 * yield/96.0;
	int least = 0x00 * yield/96.0;

	for(int r=0; r<cell_h; ++r){
		for(int c=0; c<cell_w; ++c){
			pixels[c+r*w] += (0x00 << 24) + (most << 16) + (mid << 8) + least;
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
