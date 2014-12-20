#include "Frame.h"


Frame::Frame(int w, int h) : width(w), height(h)
{
	ground = new Ground(w, h);
	surface = new Surface(w, 56);

	int gr_cols = ground->getCols();

	miner = new RoboMiner(24, gr_cols/2, this);

	Cell& rmcell = ground->getCell(24, gr_cols/2);
	rmcell.hasMiner(miner);

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


Surface *Frame::getSurface() const
{
	return surface;
}

RoboMiner *Frame::getMiner() const
{
	return miner;
}
