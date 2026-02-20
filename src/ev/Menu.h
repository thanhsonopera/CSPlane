#ifndef Menu_h
#define Menu_h

#include "LTexture.h"
#include "init.h"
#include "close.h"
#include "Play.h"
#include <vector>

using namespace std;

void loadBackground(SDL_Renderer *&gRenderer, LTexture &Bg);
void loadMenuText(int x, int fsize, SDL_Renderer *&gRenderer, vector<LTexture> &menuText);
void loadLeaderboardText(int x, int fsize, SDL_Renderer *&gRenderer, vector<LTexture> &leaderboardText, vector<string> &s);
void loadTutorialText(int x, int fsize, SDL_Renderer *&gRenderer, vector<LTexture> &tutorialText);
void loadMusicChoice(int &check_mixer, Mix_Music *&gMusic);
void loadSettingText(int x, int fsize, SDL_Renderer *&gRenderer, vector<LTexture> &settingText);
void loadBackgroundOptionsText(int x, int fsize, SDL_Renderer *&gRenderer, vector<LTexture> &backgroundOptionsText);
void loadMusicOptionsText(int x, int fsize, SDL_Renderer *&gRenderer, vector<LTexture> &musicOptionsText);


int navigateMainMenu(int keyrow, int x);
int navigateLeaderboard(int keyrow, int x);
int navigateSettingsMenu(int keyrow, int x);
int navigateTutorialMenu(int keyrow, int x);
int navigateOptionsList(int keyrow, int x);

void Solution(int &check_mixer, int &check_background, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic);
void Leaderboard(int &check_mixer, SDL_Renderer *&gRenderer, LTexture Bg, vector<string> &s, TTF_Font *gFont, Mix_Music *&gMusic);
void Tutorial(int &check_mixer, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic);
void Menu(int &check_mixer, int &check_background, SDL_Renderer *&gRenderer, vector<string> &s, LTexture Bg, SDL_Window *&gWindow, TTF_Font *gFont, TTF_Font *pFont, Mix_Music *&gMusic,
          vector<pair<int, int> > &res);

void S_background(int &check_background, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont);
void S_music(int &check_mixer, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic);
void Accept();

#endif
