#ifndef _CELL_H_
#define _CELL_H_

#include <vector>
#include <string>
#include "SDL2/SDL.h"
#include "MineralStore.h"

class Ground;
class Mineral;
class RoboMiner;

const int CELL_SZ = 4;

class Cell
{
public:
	Cell(int w=CELL_SZ, int h=CELL_SZ, int x=0, int y=0, Ground *g=nullptr);
	~Cell();
	int getWidth() const;
	int getHeight() const;
	int getX() const;
	int getY() const;
	Ground *getGround() const;
	void setGround(Ground *g);
	void addMineral(Mineral *m);
	void clearMinerals();
	int mineralCount() const;
	void drawMinerals(Uint32 *pixels);
	friend std::ostream& operator<<(std::ostream& ostr, Cell& c);
	void hasMiner(RoboMiner *rm);
	void clearMiner();
	void setVisible(bool isvis);
	bool isVisible() const;
	void setDrilled(bool isdrilled);
	void setDrilling(bool isdrilling);
	bool isDrilled() const;
	MineralStore *extract(int quant);
	int distanceFrom(const Cell& c) const;
protected:
	int width;
	int height;
	int x;
	int y;
	Ground *ground;
//	std::vector<Mineral *> minerals;
	MineralStore minerals;
	RoboMiner *miner;
	bool visible, drilling, drilled;
	void drawDrilled(Uint32 *pixels);
	void drawDrillProgress(Uint32 *pixels);
	void drawDepthShade(Uint32 *pixels, int fog);
	void drawBlank(Uint32 *pixels);
};

#endif
