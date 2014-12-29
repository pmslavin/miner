#include "Frame.h"
#include "RoboMiner.h"
#include <SDL2/SDL.h>
#include <iostream>

const int w=1024, h=896;


int main()
{
	Frame frame(w, h);
	SDL_Event event;
	RoboMiner *rm = frame.getMiner();

	bool active = true;
	bool paused = true;
	unsigned int delay = 200;

	while(active){
		frame.draw();

		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_QUIT: 	active = false;
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

		SDL_Delay(delay);
		if(!paused)
			rm->action();
	}
	std::cout << std::endl;
	return 0;
}
