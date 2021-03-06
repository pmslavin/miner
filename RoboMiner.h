#ifndef _ROBOMINER_H_
#define _ROBOMINER_H_

#include <string>
#include "Cell.h"
#include "MineralStore.h"

class Frame;
class Mineral;
class Base;


class RoboMiner
{
public:
	RoboMiner(int cy, int cx, Frame *fr=nullptr);
	virtual ~RoboMiner();
	void draw(uint32_t *pixels) const;
	int getX() const;
	int getY() const;
	void setCell(Cell *c);
	int drill(int cy, int cx);
	void move(int cy, int cx);
	void action();
	bool isFull() const;
	int getRemainingSpace() const;
	void setBase(Base *b);
	bool atBase() const;
	void listCargo() const;
	void scan();
	int ascend();
protected:
	int cell_y;
	int cell_x;
	Frame *frame;
	Base *base;
	Cell *cell, *destCell, *lastMinedOre, *drillCell;
	MineralStore cargo;
	int energy;
	int max_cargo;
	bool exploring, ascending;
	int drillCount, ascendCount;
	void emptyCargo();
	void setLastMinedOre(int cy, int cx);
	void mine();
	void process(MineralStore& ores);
	void setDestination(int cy, int cx);
	void navigate();
};

#endif
