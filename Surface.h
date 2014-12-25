#ifndef _SURFACE_H_
#define _SURFACE_H_

#include <string>
#include "SDL2/SDL.h"

typedef uint32_t Uint32;

class Frame;
class Base;

class Surface{
public:
	Surface(int w, int h, Frame *fr=nullptr);
	virtual ~Surface();
	void draw();
	const Uint32 *getPixels() const;
	Base *getBase() const;
	int getWidth() const;
	int getHeight() const;
protected:
	int width;
	int height;
	Frame *frame;
	Uint32 *pixels;
	Base *base;
	SDL_Surface *surf;
	SDL_Surface *tree;
	SDL_Surface *store;
};

#endif
