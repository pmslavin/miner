#include "Iron.h"
#include <iostream>

const std::string Iron::name = "Iron";
const std::string Iron::symbol = "Fe";

Iron::Iron(int yield) : Mineral(yield)
{

}


Iron::~Iron()
{
	std::cout << "Destructing " << name << " then... ";
}


const std::string Iron::getName() const
{
	return name;
}


const std::string Iron::getSymbol() const
{
	return symbol;
}


void Iron::draw(Uint32 *pixels)
{
//	int w = parent->getWidth();
//	int h = parent->getHeight();
	int w = 1024;
	int h = 896;
	int x = parent->getX();
	int y = parent->getY();	

	pixels[0] += 0x00FF0000*yield/512.0;
	pixels[1] += 0x00FF0000*yield/512.0;
	pixels[2] += 0x00FF0000*yield/512.0;
	pixels[3] += 0x00FF0000*yield/512.0;

	pixels[0+1*w] += 0x00FF0000*yield/512.0;
	pixels[1+1*w] += 0x00FF0000*yield/512.0;
	pixels[2+1*w] += 0x00FF0000*yield/512.0;
	pixels[3+1*w] += 0x00FF0000*yield/512.0;

	pixels[0+2*w] += 0x00FF0000*yield/512.0;
	pixels[1+2*w] += 0x00FF0000*yield/512.0;
	pixels[2+2*w] += 0x00FF0000*yield/512.0;
	pixels[3+2*w] += 0x00FF0000*yield/512.0;

	pixels[0+3*w] += 0x00FF0000*yield/512.0;
	pixels[1+3*w] += 0x00FF0000*yield/512.0;
	pixels[2+3*w] += 0x00FF0000*yield/512.0;
	pixels[3+3*w] += 0x00FF0000*yield/512.0;
}
