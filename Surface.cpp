#include "Surface.h"
#include "Base.h"
#include <cstring>


Surface::Surface(int w, int h, Frame *fr) : width(w),
					    height(h),
					    frame(fr)
{
//	pixels = new Uint32[w*h];
	base = new Base(24, 20, 0, 128, this);
	tree = SDL_LoadBMP("trees1.bmp");
	silo = SDL_LoadBMP("silo1.bmp");
	surf = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	pixels = static_cast<Uint32 *>(surf->pixels);

	SDL_SetColorKey(tree, SDL_TRUE, 0x00);
	SDL_SetColorKey(silo, SDL_TRUE, 0x00);
}


Surface::~Surface()
{
//	delete [] pixels;
	delete base;
	pixels = nullptr;
	SDL_FreeSurface(tree);
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
			pixels[i*width+j] = 0x00528EFF;	
		}
	}

	for(i=height-grass_height; i<height-soil_height; ++i){
		for(j=0; j<width; ++j){
			pixels[i*width+j] = 0x0029E639;	
		}
		pixels[i*width+width/2] = 0x00818582;
		pixels[i*width+width/2+1] = 0x00818582;
		pixels[i*width+width/2+2] = 0x00818582;
		pixels[i*width+width/2+3] = 0x00818582;
	}

	for(i=height-soil_height; i<height; ++i){
		for(j=0; j<width; ++j){
			pixels[i*width+j] = 0x005C1C00;
		}
//		pixels[i*width+width/2] = 0x00818582;
		pixels[i*width+width/2] = 0x00606060;
		pixels[i*width+width/2+1] = 0x00606060;
		pixels[i*width+width/2+2] = 0x00606060;
		pixels[i*width+width/2+3] = 0x00606060;
	}

//	int basetop = height-base->getHeight()-soil_height;
//	base->draw(&pixels[width*basetop+(width/2-base->getWidth()/2)+2]);
	
	base->draw(surf);
	SDL_Rect tz = {width-120, height-tree->h-soil_height, tree->w, tree->h};
	SDL_BlitSurface(tree, nullptr, surf, &tz);
	tz.x = 40;
	SDL_BlitSurface(tree, nullptr, surf, &tz);
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
