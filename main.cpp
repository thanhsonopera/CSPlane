#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>


#include "init.h"
#include "close.h"
#include "LTexture.h"
#include "Menu.h"
#include "Constant.h"
#include "Play.h"
using namespace std;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
TTF_Font *pFont = NULL;
Mix_Music *gMusic = NULL;

LTexture Bg;
vector<pair<int, int> > res;
int check_background = 1, check_mixer = 1, n = 0;
string *s = new string[15];

int main(int argc, char *args[])
{
    init(gWindow, gRenderer, Width, Height);
    Menu(check_mixer, check_background, gRenderer, s, Bg, gWindow, gFont, pFont, gMusic, res);
    close(gWindow, gRenderer, gFont, pFont, gMusic);
    return 0;
}
