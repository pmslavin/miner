#include "Mineral.h"
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <stdexcept>

const std::string Mineral::name = "Mineral";
const std::string Mineral::symbol = "XX";

Mineral::Mineral(int yield, Cell *par) : yield(yield), parent(par)
{
/* A zero yield shouldn't be instantiated.
 * But if it is, set it to 1
 */
	if(!yield)
		yield = 1;
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


void Mineral::setYield(int y)
{
	if(y < 0)
		y = 0;

	yield = y;
}


Mineral::~Mineral()
{

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


Mineral& Mineral::operator+=(Mineral& rhs)
{
	if(typeid(*this) != typeid(rhs)){
		std::ostringstream ess;
		ess << "+= of " << getName() << " and "
		    << rhs.getName() << std::endl;
		throw std::invalid_argument(ess.str());
	}

	yield += rhs.yield;
	rhs.yield = 0;
	return *this;
}


/*
template<typename T>
T *Mineral::extract(int quant)
{
	if(quant > yield)
		quant = yield;

	yield -= quant;

	return new T(quant);
}


auto Mineral::extract(int quant) -> decltype(this)
{
	if(quant > yield)
		quant = yield;

	yield -= quant;

	typedef decltype(this) this_t;
	return new this_t(quant);
}*/
