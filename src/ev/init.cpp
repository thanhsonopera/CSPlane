#include <iostream>
#include "init.h"

using namespace std;

void init(SDL_Window *&gWindow, SDL_Renderer *&gRenderer, int Width, int Height)
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    gWindow = SDL_CreateWindow("CS Plane", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
    if (!gWindow)
    {
        cout << "Creating Window failed: " << SDL_GetError() << endl;
        return;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer)
    {
        cout << "Creating Window failed: " << SDL_GetError() << endl;
        return;
    }
}

