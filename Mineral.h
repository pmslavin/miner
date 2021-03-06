#ifndef _MINERAL_H_
#define _MINERAL_H_

#include <string>

typedef uint32_t Uint32;

#include "Cell.h"


class Mineral
{
public:
	Mineral(int yield=0, Cell* parent=nullptr);
	virtual ~Mineral();
	virtual const std::string getName() const;
	virtual const std::string getSymbol() const;
	virtual int getYield() const;
	void setYield(int y);
	friend std::ostream& operator<<(std::ostream& ostr, Mineral& m);
	Mineral& operator+=(Mineral& rhs);
	void setParent(Cell *parent);
	Cell *getParent() const;
	virtual void draw(Uint32 *pixels, int fog) = 0;
	virtual Mineral *extract(int quant) = 0;
//	auto extract(int quant) -> decltype(this);
//	template<typename T>
//	T *extract(int quant);
protected:
	static const std::string name;
	static const std::string symbol;
	int yield;
	Cell *parent;
};

#endif
