#include "Surface.h"
#include "Frame.h"
#include "Base.h"
#include "RoboMiner.h"
#include "Cell.h"
#include "constants.h"
#include "resources.h"

#include <cstring>


Surface::Surface(int w, int h, Frame *fr) : width(w),
					    height(h),
					    frame(fr)
{
	base = new Base(24, 20, 0, width/CELL_SZ/2, this);
	
/*	trees1 = SDL_LoadBMP("trees1.bmp");
	trees2 = SDL_LoadBMP("trees2.bmp");
	silo = SDL_LoadBMP("silo1.bmp");
*/
	SDL_RWops *t1_rwo = SDL_RWFromConstMem(static_cast<const void *>(trees1_bmp), trees1_bmp_len);
	SDL_RWops *t2_rwo = SDL_RWFromConstMem(static_cast<const void *>(trees2_bmp), trees2_bmp_len);
	SDL_RWops *silo1_rwo = SDL_RWFromConstMem(static_cast<const void *>(silo1_bmp), silo1_bmp_len);
	trees1 = SDL_LoadBMP_RW(t1_rwo, 1);
	trees2 = SDL_LoadBMP_RW(t2_rwo, 1);
	silo = SDL_LoadBMP_RW(silo1_rwo, 1);

	surf = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	pixels = static_cast<Uint32 *>(surf->pixels);

	SDL_SetColorKey(trees1, SDL_TRUE, 0x00);
	SDL_SetColorKey(trees2, SDL_TRUE, 0x00);
	SDL_SetColorKey(silo, SDL_TRUE, 0x00);
}


Surface::~Surface()
{
	delete base;
	pixels = nullptr;
	SDL_FreeSurface(trees1);
	SDL_FreeSurface(trees2);
	SDL_FreeSurface(silo);
	SDL_FreeSurface(surf);
}


void Surface::draw()
{
	int i, j;
	const int grass_height = 8;
	const int soil_height = 6;

	for(i=0; i<height-grass_height; ++i){
		for(j=0; j<width; ++j){
			pixels[i*width+j] = Colours::Surface::Sky;	
		}
	}

	for(i=height-grass_height; i<height-soil_height; ++i){
		for(j=0; j<width; ++j){
			pixels[i*width+j] = Colours::Surface::Grass;	
		}
	}

	for(i=height-soil_height; i<height; ++i){
		for(j=0; j<width; ++j){
			pixels[i*width+j] = Colours::Surface::Soil;
		}
		for(int k=0; k<CELL_SZ; ++k){
			pixels[i*width+width/2+k] = Colours::Surface::Shaft;
		}
	}

	base->draw(surf);
	SDL_Rect tz1 = {width-trees1->w, height-trees1->h-soil_height, trees1->w, trees1->h};
	SDL_BlitSurface(trees1, nullptr, surf, &tz1);
	tz1.x = 40;
	SDL_BlitSurface(trees1, nullptr, surf, &tz1);
	SDL_Rect tz2 = {width-trees1->w-trees2->w-20, height-trees2->h-soil_height, trees2->w, trees2->h};
	SDL_BlitSurface(trees2, nullptr, surf, &tz2);

	SDL_Rect sz = {216, height-silo->h-soil_height, silo->w, silo->h};
	SDL_BlitSurface(silo, nullptr, surf, &sz);
	sz.x += silo->w + 16;
	SDL_BlitSurface(silo, nullptr, surf, &sz);
	sz.x += silo->w + 16;
	SDL_BlitSurface(silo, nullptr, surf, &sz);
}


const Uint32 *Surface::getPixels() const
{
	return pixels;
}


Base *Surface::getBase() const
{
	return base;
}


int Surface::getWidth() const
{
	return width;
}


int Surface::getHeight() const
{
	return height;
}


void Surface::ascend(const RoboMiner& rm) const
{
	const int soil_height = 6;
	rm.draw(&pixels[(height-soil_height)*width+width/2]);
}
