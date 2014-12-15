#ifndef SDLENV_H
#define SDLENV_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

const int WIDTH = 800;
const int HEIGHT = 600;
const int BPP = 30;

extern SDL_Window *window;
extern SDL_Renderer *rend;

bool Initialise(void);
SDL_Texture *loadTexture(std::string path);

#endif
