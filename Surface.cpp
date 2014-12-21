#include "Surface.h"
#include <cstring>

Surface::Surface(int w, int h, Frame *fr) : width(w),
					    height(h),
					    frame(fr)
{
	pixels = new Uint32[w*h];
}


Surface::~Surface()
{
	delete [] pixels;
}


void Surface::draw()
{
	int i, j;
	const int grass_height = 14;
	const int soil_height = 4;

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
		pixels[i*width+width/2] = 0x00818582;
		pixels[i*width+width/2+1] = 0x00818582;
		pixels[i*width+width/2+2] = 0x00818582;
		pixels[i*width+width/2+3] = 0x00818582;
	}
}


const Uint32 *Surface::getPixels() const
{
	return pixels;
}
