#include "Copper.h"
#include <iostream>

const std::string Copper::name = "Copper";
const std::string Copper::symbol = "Cu";

Copper::Copper(int yield) : Mineral(yield)
{

}


Copper::~Copper()
{
	std::cout << "Destructing " << name << " then... ";
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
//        int w = parent->getWidth();
//	int h = parent->getHeight();
	int w = 1024;
	int h = 896;
        int x = parent->getX();
        int y = parent->getY();

//        pixels[y*w+x] = 0x00E89149;
        pixels[0] += 0x0000FFFF*yield/512.00;
        pixels[1] += 0x0000FFFF*yield/512.00;
        pixels[2] += 0x0000FFFF*yield/512.00;
        pixels[3] += 0x0000FFFF*yield/512.00;

        pixels[0+1*w] += 0x0000FFFF*yield/512.00;
        pixels[1+1*w] += 0x0000FFFF*yield/512.00;
        pixels[2+1*w] += 0x0000FFFF*yield/512.00;
        pixels[3+1*w] += 0x0000FFFF*yield/512.00;

        pixels[0+2*w] += 0x0000FFFF*yield/512.00;
        pixels[1+2*w] += 0x0000FFFF*yield/512.00;
        pixels[2+2*w] += 0x0000FFFF*yield/512.00;
        pixels[3+2*w] += 0x0000FFFF*yield/512.00;

        pixels[0+3*w] += 0x0000FFFF*yield/512.00;
        pixels[1+3*w] += 0x0000FFFF*yield/512.00;
        pixels[2+3*w] += 0x0000FFFF*yield/512.00;
        pixels[3+3*w] += 0x0000FFFF*yield/512.00;
}
