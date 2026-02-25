#include <iostream>
#include <algorithm>
#include <fstream>

#include "Play.h"
#include "Menu.h"
#include "Paths.h"

bool dk(std::pair<int, int> a, std::pair<int, int> b)
{
    if (a.first == b.first)
    {
        if (a.second > b.second) return false;
        return true;
    }
    if (a.first < b.first) return false;
    return true;
}

void xuly(int &check_background, SDL_Window *&gWindow, SDL_Renderer *&gRenderer, TTF_Font *&gFont, TTF_Font *&pFont)
{
    reset();
    loadmedia(gRenderer, gFont, pFont);
    loadbg(check_background, gRenderer);
    bool quit = false;
    bool fn = false;
    SDL_Event e;
    background = {0, Level_Height - Height, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    while (!quit)
    {
        Uint32 now = SDL_GetTicks();
        handleEvents(quit, fn, e, gRenderer, now);
        handleContinuousInput(now);
        renderBackgroundAndFinishLine(fn, gRenderer);

        if (Plane.alive1() == true) {
            if (paused == false) {
                updateHUD(gRenderer, gFont);
                updateWorld(gRenderer);
                updateLasersAndCollisions();
            }
            renderGame(gRenderer, gFont, pFont);
        } else {
            renderDeathScreen(gRenderer, pFont);
        }

        if (now / TIMING_DIV > timing) {
            Exp(gRenderer);
            timing = now / TIMING_DIV;
        }
        SDL_RenderPresent(gRenderer);
        Uint32 frameMs = SDL_GetTicks() - now;
        if (frameMs < FPS) SDL_Delay(FPS - frameMs);
    }
    close();
}
