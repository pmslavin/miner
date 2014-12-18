#ifndef _MINERAL_H_
#define _MINERAL_H_

#include <string>

class Cell;

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
	virtual void draw() = 0;
protected:
	static const std::string name;
	static const std::string symbol;
	Cell *parent;
	int yield;
};

#endif
