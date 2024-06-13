#ifndef close_h
#define close_h

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

void close(SDL_Window *&gWindow, SDL_Renderer *&gRenderer, TTF_Font *&gFont, TTF_Font *&pFont, Mix_Music *&gMusic);

#endif
