#include <iostream>
#include "LTexture.h"
#include <SDL_image.h>

LTexture::LTexture()
{
    w = 0;
    h = 0;
    mTexture = NULL;
}

void LTexture::loadfromfile(SDL_Renderer *&gRenderer, string path)
{
    close();
    SDL_Surface *gSurface = IMG_Load(path.c_str());
    SDL_SetColorKey(gSurface, SDL_TRUE, (gSurface->format, 0, 0, 0));
    if (!gSurface)
    {
        cout << "IMG_Load failed: " << SDL_GetError() << endl;
        return;
    }
    mTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    if (!mTexture) cout << "CreateTextureFromSurface failed: " << SDL_GetError() << endl;
    w = gSurface->w;
    h = gSurface->h;
    SDL_FreeSurface(gSurface);
    gSurface = NULL;
}

void LTexture::loadfromrenderedtext(SDL_Renderer *&gRenderer, TTF_Font *&gFont, string text, SDL_Color Color)
{
    close();
    SDL_Surface *gSurface = TTF_RenderText_Solid(gFont, text.c_str(), Color);
    mTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    w = gSurface->w;
    h = gSurface->h;
    SDL_FreeSurface(gSurface);
    gSurface = NULL;
}

void LTexture::render(SDL_Renderer *&gRenderer, int x, int y, SDL_Rect *p)
{
    SDL_Rect tam = {x, y, w, h};
    if (p != NULL)
    {
        tam.w = p->w;
        tam.h = p->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, p, &tam);
}

int LTexture::getHeight()
{
    return h;
}

int LTexture::getWidth()
{
    return w;
}

void LTexture::close()
{
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    w = 0;
    h = 0;
}
