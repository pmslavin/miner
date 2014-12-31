#ifndef _BASE_H_
#define _BASE_H_

#include <vector>
#include <iostream>
#include "MineralStore.h"

class Mineral;
class Surface;
struct SDL_Surface;

class Base
{
public:
	Base(int w, int h, int y, int x, Surface *s=nullptr);
	virtual ~Base();
//	virtual void deposit(std::vector<Mineral *>& cargo);
	virtual void deposit(MineralStore& cargo);
	void listStore() const;
	int getY() const;
	int getX() const;
	virtual void draw(SDL_Surface *destsurf);
	int getWidth() const;
	int getHeight() const;
protected:
	int width, height;
	int y, x;
	Surface *surface;
//	std::vector<Mineral *> store;
	MineralStore store;
	SDL_Surface *mine;
};

#endif
