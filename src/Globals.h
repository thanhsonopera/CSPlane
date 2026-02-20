#ifndef Globals_h
#define Globals_h

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include "LTexture.h"

using namespace std;

// Global SDL objects
extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;
extern TTF_Font *pFont;
extern Mix_Music *gMusic;

// Global game objects
extern LTexture Bg;
extern vector<pair<int, int> > res;
extern int check_background;
extern int check_mixer;
extern int n;
extern vector<string> s;

#endif
