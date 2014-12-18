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


void Iron::draw()
{

}
