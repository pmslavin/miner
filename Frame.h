#ifndef _FRAME_H_
#define _FRAME_H_

#include "Ground.h"
#include "Surface.h"
#include "SDL2/SDL.h"

class Cell;
class RoboMiner;


class Frame
{
public:
	Frame(int w, int h);
	virtual ~Frame();
	Surface *getSurface() const;
	Ground *getGround() const;
	RoboMiner *getMiner() const;
	void draw();
protected:
	int width;
	int height;
	Ground *ground;
	Surface *surface;
	RoboMiner *miner;
	SDL_Rect upper, lower;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
};

#endif
