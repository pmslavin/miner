#include "Iron.h"
#include "Copper.h"
#include "Cell.h"
#include "Frame.h"
#include <SDL2/SDL.h>

#include <iostream>
const int w=1024, h=896;

int main()
{

//	Ground g(w, h);
//	Surface s(w, 56);
	Frame frame(w, h);
	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("Miner", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h+56);

//	Uint32 *pixels = new Uint32[w*h];
//	memset(pixels, 0x00, w*h*sizeof(Uint32));

//	Iron fe(17), feRich(155);
/*	Iron *fe = new Iron(17);
	Iron *feRich = new Iron(155);
	Copper *cu = new Copper(33);
	Cell c;
	Cell& tc = g.getCell(24, 36);
	
	std::cout << "Ground: " << g.getRows() << "x"
		  << g.getCols() << std::endl;
*/
/*	std::cout << fe;
	std::cout << *feRich;
	std::cout << *cu;

	c.addMineral(feRich);
	c.addMineral(cu);
	tc.addMineral(fe);
	std::cout << tc;

	std::cout << "mineralCount: " << c.mineralCount() << std::endl;
	std::cout << c;
	c.clearMinerals();
	std::cout << "mineralCount: " << c.mineralCount() << std::endl;
*/
//	std::cout << *fe;
//	std::cout << *cu;

//	g.calcMinerals();

/*	for(int i=0; i<g.getRows(); ++i){
		for(int j=0; j<g.getCols(); ++j){
			std::cout << g.getCell(i, j);
		}
	}
*/
/*	g.draw();
	s.draw();

	SDL_Rect lower = {0, 56, w, h};
	SDL_Rect upper = {0, 0, w, 56};
*/
//	frame.getGround()->calcMinerals();
	RoboMiner *rm = frame.getMiner();

	bool active = true;
	bool paused = false;
	unsigned int delay = 100;

	while(active){
//		SDL_UpdateTexture(texture, &upper, s.getPixels(), w*sizeof(Uint32));
//		SDL_UpdateTexture(texture, &lower, g.getPixels(), w*sizeof(Uint32));
		frame.draw(texture);
//		SDL_WaitEvent(&event);

		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
				active = false;
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_q)
					active = false;
				if(event.key.keysym.sym == SDLK_p)
					paused = !paused;
				if(event.key.keysym.sym == SDLK_COMMA)
					delay = (delay <= 20) ? 0 : (delay-20);
				if(event.key.keysym.sym == SDLK_PERIOD)
					delay += 20;
				break;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		SDL_Delay(delay);
		if(!paused)
			rm->action();
//		rm->move(25, 25);
	}

//	g.clearCells();
//	delete[] pixels;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
