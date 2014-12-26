#include "Surface.h"
#include "Base.h"
#include "constants.h"
#include <cstring>


Surface::Surface(int w, int h, Frame *fr) : width(w),
					    height(h),
					    frame(fr)
{
//	pixels = new Uint32[w*h];
	base = new Base(24, 20, 0, 128, this);
	
	trees1 = SDL_LoadBMP("trees1.bmp");
	trees2 = SDL_LoadBMP("trees2.bmp");
	silo = SDL_LoadBMP("silo1.bmp");

	surf = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	pixels = static_cast<Uint32 *>(surf->pixels);

	SDL_SetColorKey(trees1, SDL_TRUE, 0x00);
	SDL_SetColorKey(trees2, SDL_TRUE, 0x00);
	SDL_SetColorKey(silo, SDL_TRUE, 0x00);
}


Surface::~Surface()
{
//	delete [] pixels;
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
/*		pixels[i*width+width/2] = 0x00818582;
		pixels[i*width+width/2+1] = 0x00818582;
		pixels[i*width+width/2+2] = 0x00818582;
		pixels[i*width+width/2+3] = 0x00818582;
*/	}

	for(i=height-soil_height; i<height; ++i){
		for(j=0; j<width; ++j){
			pixels[i*width+j] = Colours::Surface::Soil;
		}
		pixels[i*width+width/2] = Colours::Surface::Shaft;
		pixels[i*width+width/2+1] = Colours::Surface::Shaft;
		pixels[i*width+width/2+2] = Colours::Surface::Shaft;
		pixels[i*width+width/2+3] = Colours::Surface::Shaft;
	}

//	int basetop = height-base->getHeight()-soil_height;
//	base->draw(&pixels[width*basetop+(width/2-base->getWidth()/2)+2]);
	
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
