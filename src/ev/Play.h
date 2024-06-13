#ifndef Play_h
#define Play_h

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <cstdlib>


#include "Constant.h"
#include "init.h"
#include "LTexture.h"
#include "Object.h"
#include "MyBullet.h"
#include "MyPlane.h"
#include "EnemyBullet.h"
#include "EnemyPlane.h"
#include "EnemyPlane2.h"
#include "Rocket.h"
#include "HP.h"
#include "BigBang.h"
#include "Compare.h"
#include "CheckCollision.h"


void sinh(SDL_Renderer *&gRenderer, int sl1, int sl2);
void update(SDL_Renderer *&gRenderer);
void Exp(SDL_Renderer *&gRenderer);
void loadmedia(SDL_Renderer *&gRenderer, TTF_Font *&gFont, TTF_Font *&pFont);
void loadbg(int &check_background, SDL_Renderer *&gRenderer);
void xuly(int &check_background, SDL_Window *&gWindow, SDL_Renderer *&gRenderer, TTF_Font *&gFont, TTF_Font *&pFont);

#endif
