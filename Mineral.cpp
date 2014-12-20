#include "Mineral.h"

#include <iostream>

const std::string Mineral::name = "Mineral";
const std::string Mineral::symbol = "XX";

Mineral::Mineral(int yield, Cell *par) : yield(yield), parent(par)
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
//	std::cout << "Destructing " << name << std::endl;
}

std::ostream& operator<<(std::ostream& ostr, Mineral& m)
{
	ostr << m.getName() << " (" << m.getSymbol() << ") "
	     << "Yield: " << m.getYield() << "  Parent: "
	     << m.getParent() << std::endl;

	return ostr;
}


void Mineral::setParent(Cell *par)
{
	parent = par;
}


Cell *Mineral::getParent() const
{
	return parent;
}

