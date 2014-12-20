#ifndef _COPPER_H_
#define _COPPER_H_

#include "Mineral.h"

class Copper : public Mineral
{
public:
	Copper(int yield);
	~Copper();
	const std::string getName() const;
	const std::string getSymbol() const;
	void draw(Uint32 *pixels);
	Copper *extract(int quant);
protected:
	static const std::string name;
	static const std::string symbol;
};

#endif
