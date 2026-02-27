#include <iostream>
#include <cstdio>
#ifdef _WIN32
#include <direct.h>
#endif
#include "init.h"

using namespace std;

void init(SDL_Window *&gWindow, SDL_Renderer *&gRenderer, int Width, int Height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return;
    }
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    int initted = IMG_Init(imgFlags);
    (void)initted; 
    if (TTF_Init() != 0) {
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
        return;
    }
    (void)Mix_Init; 
    gWindow = SDL_CreateWindow("CS Plane", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
    if (!gWindow)
    {
        return;
        return;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer)
    {
        return;
    }
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
    SDL_RenderSetLogicalSize(gRenderer, Width, Height);
}

