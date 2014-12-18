#ifndef _GOLD_H_
#define _GOLD_H_

#include "Mineral.h"

class Gold : public Mineral
{
public:
	Gold(int yield);
	~Gold();
	const std::string getName() const;
	const std::string getSymbol() const;
	void draw(Uint32 *pixels);
protected:
	static const std::string name;
	static const std::string symbol;
};

#endif
