#ifndef _GROUND_H_
#define _GROUND_H_

#include <vector>
#include "Cell.h"

class Frame;
struct SDL_Surface;


class Ground
{
public:
	Ground(int w, int h, Frame *fr=nullptr);
	virtual ~Ground();
	Cell& getCell(int y, int x);
	int getRows() const;
	int getCols() const;
	int getWidth() const;
	int getHeight() const;
	void calcMinerals();
	void clearCells();
	void draw();
	const Uint32 *getPixels() const;
	SDL_Surface *getSurf() const;
protected:
	int width;
	int height;
	Frame *frame;
	std::vector<Cell> cells;
	int cell_cols;
	int cell_rows;
	Uint32 *pixels;
	SDL_Surface *surf;
};

#endif
