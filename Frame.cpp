#include "Frame.h"


Frame::Frame(int w, int h) : width(w), height(h)
{
	ground = new Ground(w, h);
	surface = new Surface(w, 56);

	lower = {0, 56, w, h};
	upper = {0, 0, w, 56};
}


Frame::~Frame()
{
	delete ground;
	delete surface;
}


void Frame::draw(SDL_Texture *texture)
{
	surface->draw();
	ground->draw();

	SDL_UpdateTexture(texture, &upper, surface->getPixels(), width*sizeof(Uint32));
	SDL_UpdateTexture(texture, &lower, ground->getPixels(), width*sizeof(Uint32));
}


Ground *Frame::getGround() const
{
	return ground;
}
