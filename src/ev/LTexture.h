#ifndef LTexture_h
#define LTexture_h

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Constant.h"


using namespace std;

class LTexture
{
    int w;
    int h;
    SDL_Texture *mTexture;
public:
    LTexture();
    void loadfromfile(SDL_Renderer *&gRenderer, string path);
    void loadfromrenderedtext(SDL_Renderer *&gRenderer, TTF_Font *&gFont, string text, SDL_Color Color);
    void render(SDL_Renderer *&gRenderer, int x, int y, SDL_Rect *p = NULL);
    int getWidth();
    int getHeight();
    void close();
};

#endif

