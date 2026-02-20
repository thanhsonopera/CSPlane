#include <iostream>
#include "LTexture.h"
#include <SDL_image.h>
#include "Paths.h"

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
    string tried = path;
    if (!gSurface)
    {
        string alt = imgPath("", path);
        gSurface = IMG_Load(alt.c_str());
        tried += " (also tried: " + alt + ")";
    }
    if (!gSurface)
    {
        return;
    }
    SDL_SetColorKey(gSurface, SDL_TRUE, SDL_MapRGB(gSurface->format, 0, 0, 0));
    mTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    if (!mTexture) (void)SDL_GetError();
    w = gSurface->w;
    h = gSurface->h;
    SDL_FreeSurface(gSurface);
    gSurface = NULL;
}

void LTexture::loadfromrenderedtext(SDL_Renderer *&gRenderer, TTF_Font *&gFont, string text, SDL_Color Color)
{
    close();
    if (!gFont) return;

    // Render smooth text (blended) with a soft shadow by compositing two surfaces
    SDL_Color shadowColor = {0, 0, 0, 160};
    int shadowOffsetX = 2;
    int shadowOffsetY = 2;

    SDL_Surface *surfMain = TTF_RenderText_Blended(gFont, text.c_str(), Color);
    if (!surfMain) return;
    SDL_Surface *surfShadow = TTF_RenderText_Blended(gFont, text.c_str(), shadowColor);
    if (!surfShadow) {
        // fallback: use main only
        mTexture = SDL_CreateTextureFromSurface(gRenderer, surfMain);
        if (mTexture) SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
        w = surfMain->w; h = surfMain->h;
        SDL_FreeSurface(surfMain);
        return;
    }

    int cw = std::max(surfMain->w, surfShadow->w + shadowOffsetX);
    int ch = std::max(surfMain->h, surfShadow->h + shadowOffsetY);

    // Create a combined RGBA surface
    SDL_Surface *combined = SDL_CreateRGBSurface(0, cw, ch, 32,
                                                 0x00FF0000,
                                                 0x0000FF00,
                                                 0x000000FF,
                                                 0xFF000000);
    if (!combined) {
        SDL_FreeSurface(surfMain);
        SDL_FreeSurface(surfShadow);
        return;
    }

    SDL_SetSurfaceBlendMode(surfShadow, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceBlendMode(surfMain, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceBlendMode(combined, SDL_BLENDMODE_BLEND);

    SDL_Rect dstShadow = { shadowOffsetX, shadowOffsetY, surfShadow->w, surfShadow->h };
    SDL_Rect dstMain = { 0, 0, surfMain->w, surfMain->h };

    SDL_BlitSurface(surfShadow, NULL, combined, &dstShadow);
    SDL_BlitSurface(surfMain, NULL, combined, &dstMain);

    mTexture = SDL_CreateTextureFromSurface(gRenderer, combined);
    if (mTexture) SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
    w = combined->w; h = combined->h;

    SDL_FreeSurface(surfMain);
    SDL_FreeSurface(surfShadow);
    SDL_FreeSurface(combined);
}

void LTexture::render(SDL_Renderer *&gRenderer, int x, int y, SDL_Rect *p)
{
    SDL_Rect tam = {x, y, w, h};
    if (p != NULL)
    {
        tam.w = p->w;
        tam.h = p->h;
    }
    if (!mTexture) {
        // avoid crashing when texture is null
        // cout << "LTexture::render: texture is NULL" << endl;
        return;
    }
    SDL_RenderCopy(gRenderer, mTexture, p, &tam);
}

void LTexture::renderEx(SDL_Renderer *&gRenderer, int x, int y, double scale, Uint8 alpha)
{
    if (!mTexture) return;
    int dw = static_cast<int>(w * scale);
    int dh = static_cast<int>(h * scale);
    SDL_Rect dest = { x - (dw - w) / 2, y - (dh - h) / 2, dw, dh };
    SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(mTexture, alpha);
    SDL_RenderCopy(gRenderer, mTexture, NULL, &dest);
    SDL_SetTextureAlphaMod(mTexture, 255);
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
