#ifndef _FRAME_H_
#define _FRAME_H_

#include "Ground.h"
#include "Surface.h"
#include "RoboMiner.h"
#include "SDL2/SDL.h"

class Cell;

class Frame
{
public:
	Frame(int w, int h);
	virtual ~Frame();
	Surface *getSurface() const;
	Ground *getGround() const;
	RoboMiner *getMiner() const;
	void draw(SDL_Texture *texture);
protected:
	int width;
	int height;
	SDL_Rect upper;
	SDL_Rect lower;
	Ground *ground;
	Surface *surface;
	RoboMiner *miner;
};

#endif
