#include "Frame.h"
#include "RoboMiner.h"

#include <iostream>


Frame::Frame(int w, int h) : width(w),
       			     height(h),
			     window(nullptr),
			     renderer(nullptr),
			     texture(nullptr)
{
	const int surface_height = 64;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Miner", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h+surface_height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h+surface_height);

//	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

	ground = new Ground(w, h);
	surface = new Surface(w, surface_height);

	int gr_cols = ground->getCols();
//	int gr_rows = ground->getRows();

	miner = new RoboMiner(0, gr_cols/2, this);

	lower = {0, surface_height, w, h};
	upper = {0, 0, w, surface_height};
	surface->draw();
	SDL_UpdateTexture(texture, &upper, surface->getPixels(), width*sizeof(Uint32));

	srand(1977);
}


Frame::~Frame()
{
	delete ground;
	delete surface;
	delete miner;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void Frame::draw()
{
// Surface is immobile at present...
//	surface->draw();
	SDL_UpdateTexture(texture, &upper, surface->getPixels(), width*sizeof(Uint32));
	ground->draw();

/*	Texture-based route...
	SDL_Texture *grText = SDL_CreateTextureFromSurface(renderer, ground->getSurf());
	SDL_Rect grRect = {0, surface->getHeight(), ground->getWidth(), ground->getHeight()};
	SDL_Rect suRect = {0, 0, surface->getWidth(), surface->getHeight()};
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, &suRect, &suRect);
	SDL_RenderCopy(renderer, grText, NULL, &grRect);
	SDL_DestroyTexture(grText);
*/
	SDL_UpdateTexture(texture, &lower, ground->getPixels(), width*sizeof(Uint32));
//	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
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
