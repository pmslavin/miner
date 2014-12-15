#include "sdlenv.h"

SDL_Window *window = NULL;
SDL_Renderer *rend = NULL;

bool Initialise(void)
{
	if( SDL_Init( SDL_INIT_VIDEO) < 0){
		fprintf(stderr, "[SDL] Unable to initialise SDL.");
		return false;
	}
	window = SDL_CreateWindow("Sprite Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if(!window){
		fprintf(stderr, "[SDL] Unable to create SDL window.");
		return false;
	}
	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(!rend){
		fprintf(stderr, "[SDL] Unable to create renderer.");
		return false;
	}
	SDL_SetRenderDrawColor( rend, 0x0, 0x0, 0x0, 0x0 );
	IMG_Init(IMG_INIT_PNG);

	return true;
}


SDL_Texture *loadTexture(std::string path)
{
	return NULL;
}
