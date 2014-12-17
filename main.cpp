#include "Mineral.h"
#include "Iron.h"
#include "Copper.h"
#include "Cell.h"
#include <iostream>

int main(int argc, char *argv[])
{

	Mineral m;	
	Iron fe(17);
	Copper *cu = new Copper(33);
	Cell c;
	
	std::cout << m;
	std::cout << fe;
	std::cout << *cu;

	c.addMineral(&m);
	c.addMineral(&fe);
	c.addMineral(cu);

	std::cout << "mineralCount: " << c.mineralCount() << std::endl;
	std::cout << c;
	c.clearMinerals();
	std::cout << "mineralCount: " << c.mineralCount() << std::endl;

	delete cu;

	return 0;
}
