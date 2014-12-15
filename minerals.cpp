#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>

const int w = 1200;
const int h = 912;

int main(int argc, char ** argv)
{

	bool active = true;
//	int w, h;
	SDL_Event event;
//	SDL_DisplayMode mode;

	SDL_Init(SDL_INIT_VIDEO);
//	SDL_GetCurrentDisplayMode(0, &mode);
//	w = mode.w;
//	h = mode.h;

	SDL_Window *window = SDL_CreateWindow("Mineral Field", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);

	Uint32 *pixels = new Uint32[w*h];
//	memset(pixels, 0x00, w*h*sizeof(Uint32));

	Uint32 faderange = 24;

	for(int y=0; y<h; y+=h/faderange){
		Uint32 fadestep = faderange - y/(h/faderange) - 1;
		Uint32 fade = (0x00 << 24) + ((fadestep+12) << 16) + ((fadestep+2) << 8) + (fadestep+1);
//		Uint32 fade = (fadestep << 24) + (fadestep << 16) + (fadestep << 8) + 0x00;
//		Uint32 fade = (0x00 << 24) + (0xFF << 16) + (0x00 << 8) + 0x00;
//		Uint32 fade = 0x00000000;
		printf("y: %d : %08x\n", y, fade);
//		memset(&pixels[y*w], fade, h/faderange*w*sizeof(Uint32));
		for(unsigned int p=y; p<y+h/faderange; p++)
			for(int x=0; x<w; x++)
				pixels[p*w+x] = fade;
	}


	for(int y=1; y<(h-1); y++){
    		for(int x=0; x<(w-1); x++){
			if((rand()%h) > 1.2*(h-y) && rand()%512 == 256){
				pixels[w*y+x] = 0x000000FF;
/*				pixels[w*(y+1)+x] = 0x000000FF;
				pixels[w*(y-1)+x] = 0x000000FF;
				pixels[w*y+x+1] = 0x000000FF;
				pixels[w*y+x-1] = 0x000000FF;
*/			}

			if((rand()%h) > 1.3*(h-y) && rand()%768 == 256){
				pixels[w*y+x] = 0x00FF0000;
				pixels[w*(y+1)+x] = 0x00500000;
				pixels[w*(y+1)+x+1] = 0x00200000;
				pixels[w*(y+1)+x-1] = 0x00200000;
				pixels[w*(y-1)+x] = 0x00500000;
				pixels[w*(y-1)+x+1] = 0x00200000;
				pixels[w*(y-1)+x-1] = 0x00200000;
				pixels[w*y+x+1] = 0x00500000;
				pixels[w*y+x-1] = 0x00500000;
			}

			if((rand()%h) > 1.7*(h-y) && rand()%(1024+(int)1.2*y) == 256){
				pixels[w*y+x] = 0x0000FF00;
				pixels[w*y+x-1] = 0x0000FF00;
				pixels[w*y+x+1] = 0x0000FF00;
				pixels[w*(y+1)+x-1] = 0x00006000;
				pixels[w*(y+1)+x] = 0x0000FF00;
				pixels[w*(y+1)+x+1] = 0x00006000;
				pixels[w*(y-1)+x-1] = 0x00006000;
				pixels[w*(y-1)+x] = 0x0000FF00;
				pixels[w*(y-1)+x+1] = 0x00006000;
			}

			if((rand()%h) > 2.2*(h-y) && rand()%2048 == 256){
				pixels[w*y+x] = 0x00FFFF00;
/*				pixels[w*(y-1)+x] = 0x00FFFF00;
				pixels[w*(y+1)+x] = 0x00FFFF00;
				pixels[w*y+x+1] = 0x00FFFF00;
				pixels[w*y+x-1] = 0x00FFFF00;
*/			}

			if((rand()%h) > 3.1*(h-y) && rand()%3072 == 256){
				pixels[w*y+x] = 0x00FFFFFF;
				pixels[w*(y+1)+x] = 0x00FFFFFF;
				pixels[w*(y-1)+x] = 0x00FFFFFF;
				pixels[w*y+x+1] = 0x00FFFFFF;
				pixels[w*y+x-1] = 0x00FFFFFF;
			}
			
	/*		if(rand() < (RAND_MAX/(9*(h-y)*log(5+h-y))) )
				pixels[w*y+x] = 0x00FF00FF;

			if(rand() < (RAND_MAX/(15*(h-y)*log(5+h-y))) )
				pixels[w*y+x] = 0x00FF0000;
	*/	}
	}

    while(active){
        SDL_UpdateTexture(texture, NULL, pixels, w*sizeof(Uint32));
        SDL_WaitEvent(&event);

        switch(event.type){
		case SDL_QUIT:
			active = false;
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_q)
				active = false;
			break;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
