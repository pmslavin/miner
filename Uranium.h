#ifndef _URANIUM_H_
#define _URANIUM_H__

#include "Mineral.h"

class Uranium : public Mineral
{
public:
	Uranium(int yield);
	~Uranium();
	const std::string getName() const;
	const std::string getSymbol() const;
	void draw(Uint32 *pixels, int fog);
	Uranium *extract(int quant);
protected:
	static const std::string name;
	static const std::string symbol;
};

#endif
