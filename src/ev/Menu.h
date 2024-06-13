#ifndef Menu_h
#define Menu_h

#include "LTexture.h"
#include "init.h"
#include "close.h"
#include "Play.h"

void loadMedia_1(SDL_Renderer *&gRenderer, LTexture &Bg);
void loadMedia_2(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture);
void loadMedia_3(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_2, string *&s);
void loadMedia_4(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_3);
void loadMedia_5(int &check_mixer, Mix_Music *&gMusic);
void loadMedia_6(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_4);
void loadMedia_7();
void loadMedia_8(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_6);
void loadMedia_9(int x, int fsize, SDL_Renderer *&gRenderer, LTexture *&gTextTexture_7);


int Update(int keyrow, int x);
int Update_2(int keyrow, int x);
int Update_3(int keyrow, int x);
int Update_4(int keyrow, int x);
int Update_5(int keyrow, int x);

void Solution(int &check_mixer, int &check_background, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic);
void Leaderboard(int &check_mixer, SDL_Renderer *&gRenderer, LTexture Bg, string *&s, TTF_Font *gFont, Mix_Music *&gMusic);
void Tutorial(int &check_mixer, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic);
void Menu(int &check_mixer, int &check_background, SDL_Renderer *&gRenderer, string *&s, LTexture Bg, SDL_Window *&gWindow, TTF_Font *gFont, TTF_Font *pFont, Mix_Music *&gMusic,
          vector<pair<int, int> > &res);

void S_background(int &check_background, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont);
void S_music(int &check_mixer, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic);
void Accept();

#endif
