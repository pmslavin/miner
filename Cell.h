#ifndef _CELL_H_
#define _CELL_H_

#include <vector>
#include <string>

class Frame;
class Mineral;

class Cell
{
public:
	Cell(int w=1, int h=1, int x=0, int y=0, Frame *fr=nullptr);
	~Cell();
	int getWidth() const;
	int getHeight() const;
	int getX() const;
	int getY() const;
	Frame *getFrame() const;
	void setFrame(Frame *fr);
	void addMineral(Mineral *m);
	void clearMinerals();
	int mineralCount() const;
	friend std::ostream& operator<<(std::ostream& ostr, Cell& c);
protected:
	int width;
	int height;
	int x;
	int y;
	Frame *frame;
	std::vector<Mineral *> minerals;
};

#endif
