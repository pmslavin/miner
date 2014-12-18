#ifndef _MINERAL_H_
#define _MINERAL_H_

#include <string>
#include <SDL2/SDL.h>

#include "Cell.h"

class Mineral
{
public:
	Mineral(int yield=0, Cell* parent=nullptr);
	virtual ~Mineral();
	virtual const std::string getName() const;
	virtual const std::string getSymbol() const;
	virtual int getYield() const;
	friend std::ostream& operator<<(std::ostream& ostr, Mineral& m);
	void setParent(Cell *parent);
	Cell *getParent() const;
	virtual void draw(Uint32 *pixels) = 0;
protected:
	static const std::string name;
	static const std::string symbol;
	Cell *parent;
	int yield;
};

#endif
