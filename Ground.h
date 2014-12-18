#ifndef _GROUND_H_
#define _GROUND_H_

#include <vector>
#include "Cell.h"

class Frame;


class Ground
{
public:
	Ground(int w, int h, Frame *fr=nullptr);
	virtual ~Ground();
	Cell& getCell(int x, int y);
	int getRows() const;
	int getCols() const;
	int getWidth() const;
	int getHeight() const;
	void calcMinerals();
	void clearCells();
	void draw(Uint32 *pixels);
protected:
	int width;
	int height;
	Frame *frame;
	std::vector<Cell> cells;
	int cell_cols;
	int cell_rows;
};

#endif
