#ifndef _DIAMOND_H_
#define _DIAMOND_H_

#include "Mineral.h"

class Diamond : public Mineral
{
public:
	Diamond(int yield);
	~Diamond();
	const std::string getName() const;
	const std::string getSymbol() const;
	void draw(Uint32 *pixels);
protected:
	static const std::string name;
	static const std::string symbol;
};

#endif
