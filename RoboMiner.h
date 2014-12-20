#ifndef _ROBOMINER_H_
#define _ROBOMINER_H_

#include <string>
#include "Cell.h"

class Frame;
class Mineral;

class RoboMiner
{
public:
	RoboMiner(int cy, int cx, Frame *fr=nullptr);
	virtual ~RoboMiner();
	void draw(uint32_t *pixels);
	int getX() const;
	int getY() const;
	void setCell(Cell *c);
	int drill(int cy, int cx);
	void move(int cy, int cx);
	void action();
	void mine();
	void process(std::vector<Mineral *> *ores);
protected:
	int cell_y;
	int cell_x;
	Frame *frame;
	Cell *cell;
	std::vector<Mineral *> cargo;
	int energy;
};

#endif
