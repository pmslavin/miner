#ifndef _SURFACE_H_
#define _SURFACE_H_

#include <string>
#include "SDL2/SDL.h"

typedef uint32_t Uint32;

class Frame;
class Base;
class RoboMiner;

class Surface{
public:
	Surface(int w, int h, Frame *fr=nullptr);
	virtual ~Surface();
	void draw();
	const Uint32 *getPixels() const;
	Base *getBase() const;
	int getWidth() const;
	int getHeight() const;
	void ascend(const RoboMiner& rm) const;
protected:
	int width;
	int height;
	Frame *frame;
	Uint32 *pixels;
	Base *base;
	SDL_Surface *surf;
	SDL_Surface *trees1;
	SDL_Surface *trees2;
	SDL_Surface *silo;
};

#endif
