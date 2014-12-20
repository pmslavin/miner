#ifndef _IRON_H_
#define _IRON_H_

#include "Mineral.h"

class Iron : public Mineral
{
public:
	Iron(int yield);
	~Iron();
	const std::string getName() const;
	const std::string getSymbol() const;
	void draw(Uint32 *pixels);
	Iron *extract(int quant);
protected:
	static const std::string name;
	static const std::string symbol;
};

#endif
