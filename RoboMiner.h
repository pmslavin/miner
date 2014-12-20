#ifndef _ROBOMINER_H_
#define _ROBOMINER_H_

#include <string>
#include "Cell.h"

class Frame;
class Mineral;

class RoboMiner
{
public:
	RoboMiner(int cx, int cy, Frame *fr=nullptr);
	virtual ~RoboMiner();
	void draw(uint32_t *pixels);
	int getX() const;
	int getY() const;
	void setCell(Cell *c);
	int drill(int cx, int cy);
	void move(int cx, int cy);
	void action();
	void mine();
protected:
	int cell_x;
	int cell_y;
	Frame *frame;
	Cell *cell;
	std::vector<Mineral *> cargo;
	int energy;
};

#endif
