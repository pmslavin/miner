#include "Frame.h"

#include <iostream>


Frame::Frame(int w, int h) : width(w), height(h)
{
	const int surface_height = 64;

	ground = new Ground(w, h);
	surface = new Surface(w, surface_height);

	int gr_cols = ground->getCols();
//	int gr_rows = ground->getRows();

	miner = new RoboMiner(0, gr_cols/2, this);

	Cell& rmcell = ground->getCell(0, gr_cols/2);
	rmcell.hasMiner(miner);
	rmcell.setDrilled(true);

	lower = {0, surface_height, w, h};
	upper = {0, 0, w, surface_height};
	surface->draw();

	srand(1977);
}


Frame::~Frame()
{
	delete ground;
	delete surface;
}


void Frame::draw(SDL_Texture *texture)
{
//	surface->draw();
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
