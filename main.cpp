#include "Iron.h"
#include "Copper.h"
#include "Cell.h"
#include "Ground.h"
#include <iostream>

int main(int argc, char *argv[])
{

	Ground g(1024, 896);

	Iron fe(17), feRich(155);
	Copper *cu = new Copper(33);
	Cell c;
	Cell& tc = g.getCell(24, 36);
	
	std::cout << "Ground: " << g.getRows() << "x"
		  << g.getCols() << std::endl;

	std::cout << fe;
	std::cout << feRich;
	std::cout << *cu;

	c.addMineral(&fe);
	c.addMineral(cu);
	tc.addMineral(&feRich);
	std::cout << tc;

	std::cout << "mineralCount: " << c.mineralCount() << std::endl;
	std::cout << c;
	c.clearMinerals();
	std::cout << "mineralCount: " << c.mineralCount() << std::endl;

	std::cout << fe;
	std::cout << *cu;

	delete cu;

	return 0;
}
