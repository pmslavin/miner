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


void Copper::draw()
{

}
