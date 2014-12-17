#include "Mineral.h"

#include <iostream>

const std::string Mineral::name = "Mineral";
const std::string Mineral::symbol = "XX";

Mineral::Mineral(int yield) : yield(yield)
{

}


const std::string Mineral::getName() const
{
	return name;
}


const std::string Mineral::getSymbol() const
{
	return symbol;
}


int Mineral::getYield() const
{
	return yield;
}


Mineral::~Mineral()
{
	std::cout << "Destructing " << name << std::endl;
}

std::ostream& operator<<(std::ostream& ostr, Mineral& m)
{
	ostr << m.getName() << " (" << m.getSymbol() << ") "
	     << "Yield: " << m.getYield() << std::endl;

	return ostr;
}

/*
Mineral::Mineral(int weight, int val) : weight(weight),
       					value(val)
{
	
}

int Mineral::getWeight() const
{
	return weight;
}


int Mineral::getValue() const
{
	return value;
}
*/
