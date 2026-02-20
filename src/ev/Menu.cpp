#include <iostream>
#include <vector>

#include "Menu.h"
#include "Paths.h"

using namespace std;

void loadBackground(SDL_Renderer *&gRenderer, LTexture &Bg)
{
    Bg.loadfromfile(gRenderer, imgBg("homebg1.jpg") );
}

void loadMenuText(int x, int fsize, SDL_Renderer *&gRenderer, vector<LTexture> &menuText)
{
    TTF_Font *gFont = TTF_OpenFont( "font/VGOUDYB.TTF", fsize );
    if (!gFont) return;
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 1) menuText[0].loadfromrenderedtext(gRenderer, gFont, "PLAY", textColor2);
    else menuText[0].loadfromrenderedtext(gRenderer, gFont, "PLAY", textColor);
    if (x == 2) menuText[1].loadfromrenderedtext(gRenderer, gFont, "LEADERBOARD", textColor2);
    else menuText[1].loadfromrenderedtext(gRenderer, gFont, "LEADERBOARD", textColor);
    if (x == 3) menuText[2].loadfromrenderedtext(gRenderer, gFont, "SETTING", textColor2);
    else menuText[2].loadfromrenderedtext(gRenderer, gFont, "SETTING", textColor);
    if (x == 4) menuText[3].loadfromrenderedtext(gRenderer, gFont, "TUTORIAL", textColor2);
    else menuText[3].loadfromrenderedtext(gRenderer, gFont, "TUTORIAL", textColor);
    if (x == 5) menuText[4].loadfromrenderedtext(gRenderer, gFont, "EXIT", textColor2);
    else menuText[4].loadfromrenderedtext(gRenderer, gFont, "EXIT", textColor);
}

void loadLeaderboardText(int x, int fsize, SDL_Renderer *&gRenderer, vector<LTexture> &leaderboardText, vector<string> &s)
{
    TTF_Font *gFont = TTF_OpenFont( "font/VGOUDYB.TTF", fsize);
    TTF_Font *gFont1 = TTF_OpenFont( "font/VGOUDYB.TTF", 30);
    SDL_Color textColor = {255, 255, 204};
    SDL_Color textColor2 = {255, 155, 0};
    SDL_Color textColor3 = {255, 0, 0};
    if (x == 1) leaderboardText[0].loadfromrenderedtext(gRenderer, gFont, "LEADERBOARD", textColor2);
    else leaderboardText[0].loadfromrenderedtext(gRenderer, gFont, "LEADERBOARD", textColor3);

    for (int i = 0; i < 10; ++ i) {
        if (x == i + 2) leaderboardText[i + 1].loadfromrenderedtext(gRenderer, gFont1, s[i], textColor2);
        else leaderboardText[i + 1].loadfromrenderedtext(gRenderer, gFont1, s[i], textColor);
    }

    if (x == 12) leaderboardText[11].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor2);
    else leaderboardText[11].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor3);

}
void loadTutorialText(int x, int fsize, SDL_Renderer *&gRenderer, vector<LTexture> &tutorialText) {
    TTF_Font *gFont = TTF_OpenFont( "font/VGOUDYB.TTF", fsize);
    TTF_Font *gFont1 = TTF_OpenFont( "font/VAVOI.TTF", 20);
    TTF_Font *gFont2 = TTF_OpenFont( "font/VGOUDYB.TTF", 30);
    SDL_Color textColor = {255, 255, 204};
    SDL_Color textColor2 = {255, 155, 0};
    SDL_Color textColor3 = {255, 0, 0};
    if (x == 1) tutorialText[0].loadfromrenderedtext(gRenderer, gFont, "TUTORIAL", textColor2);
    else tutorialText[0].loadfromrenderedtext(gRenderer, gFont, "TUTORIAL", textColor3);
    tutorialText[1].loadfromrenderedtext(gRenderer, gFont2, "MOVE UP: UP", textColor);
    tutorialText[2].loadfromrenderedtext(gRenderer, gFont2, "MOVE DOWN: DOWN", textColor);
    tutorialText[3].loadfromrenderedtext(gRenderer, gFont2, "MOVE LEFT: LEFT", textColor);
    tutorialText[4].loadfromrenderedtext(gRenderer, gFont2, "MOVE RIGHT: RIGHT", textColor);
    tutorialText[5].loadfromrenderedtext(gRenderer, gFont2, "SHOOT: SPACE", textColor);
    tutorialText[8].loadfromrenderedtext(gRenderer, gFont2, "EXIT: E", textColor);
    tutorialText[7].loadfromrenderedtext(gRenderer, gFont2, "BACK: B", textColor);
    tutorialText[6].loadfromrenderedtext(gRenderer, gFont2, "PAUSE: P", textColor);
    tutorialText[9].loadfromrenderedtext(gRenderer, gFont1, "MADE BY SON AND QUANG", textColor);
    if (x == 2) tutorialText[10].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor2);
    else tutorialText[10].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor3);
}
void loadMusicChoice(int &check_mixer, Mix_Music *&gMusic)
{
    if (gMusic) { Mix_FreeMusic(gMusic); gMusic = NULL; }
    const char *names[3] = {"ft.mp3","h2.mp3","h3.mp3"};
    if (check_mixer >= 1 && check_mixer <= 3) {
        string name = names[check_mixer-1];
        gMusic = Mix_LoadMUS(name.c_str());
        if (!gMusic) {
            string alt = string("music/") + name;
            gMusic = Mix_LoadMUS(alt.c_str());
            (void)alt; // silence unused var if logging removed
        }
    }
}
void loadSettingText(int x, int fsize, SDL_Renderer *&gRenderer, vector<LTexture> &settingText) {
    TTF_Font *gFont = TTF_OpenFont( "font/VGOUDYB.TTF", fsize);
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Color textColor2 = {255, 155, 0};

    if (x == 1) settingText[0].loadfromrenderedtext(gRenderer, gFont, "BACKGROUND", textColor2);
    else settingText[0].loadfromrenderedtext(gRenderer, gFont, "BACKGROUND", textColor);
    if (x == 2) settingText[1].loadfromrenderedtext(gRenderer, gFont, "MUSIC", textColor2);
    else settingText[1].loadfromrenderedtext(gRenderer, gFont, "MUSIC", textColor);
    if (x == 3) settingText[2].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor2);
    else settingText[2].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor);
}

void loadBackgroundOptionsText(int x, int fsize, SDL_Renderer *&gRenderer, vector<LTexture> &backgroundOptionsText) {
    TTF_Font *gFont = TTF_OpenFont( "font/VGOUDYB.TTF", fsize);
    TTF_Font *gFont1 = TTF_OpenFont( "font/VAVOI.TTF", fsize);
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 3) backgroundOptionsText[2].loadfromrenderedtext(gRenderer, gFont1, "GALAXY", textColor2);
    else backgroundOptionsText[2].loadfromrenderedtext(gRenderer, gFont1, "GALAXY", textColor);
    if (x == 2) backgroundOptionsText[1].loadfromrenderedtext(gRenderer, gFont1, "OCEAN", textColor2);
    else backgroundOptionsText[1].loadfromrenderedtext(gRenderer, gFont1, "OCEAN", textColor);
    if (x == 1) backgroundOptionsText[0].loadfromrenderedtext(gRenderer, gFont1, "JUNGLE", textColor2);
    else backgroundOptionsText[0].loadfromrenderedtext(gRenderer, gFont1, "JUNGLE", textColor);
    if (x == 4) backgroundOptionsText[3].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor2);
    else backgroundOptionsText[3].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor);
}
void loadMusicOptionsText(int x, int fsize, SDL_Renderer *&gRenderer, vector<LTexture> &musicOptionsText) {
    TTF_Font *gFont = TTF_OpenFont( "font/VGOUDYB.TTF", fsize);
    TTF_Font *gFont1 = TTF_OpenFont( "font/VAVOI.TTF", fsize);
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Color textColor2 = {255, 155, 0};
    if (x == 3) musicOptionsText[2].loadfromrenderedtext(gRenderer, gFont1, "SOUNDTRACK3", textColor2);
    else musicOptionsText[2].loadfromrenderedtext(gRenderer, gFont1, "SOUNDTRACK3   ", textColor);
    if (x == 2) musicOptionsText[1].loadfromrenderedtext(gRenderer, gFont1, "SOUNDTRACK2", textColor2);
    else musicOptionsText[1].loadfromrenderedtext(gRenderer, gFont1, "SOUNDTRACK2", textColor);
    if (x == 1) musicOptionsText[0].loadfromrenderedtext(gRenderer, gFont1, "SOUNDTRACK1", textColor2);
    else musicOptionsText[0].loadfromrenderedtext(gRenderer, gFont1, "SOUNDTRACK1", textColor);
    if (x == 4) musicOptionsText[3].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor2);
    else musicOptionsText[3].loadfromrenderedtext(gRenderer, gFont, "BACK", textColor);
}

int navigateMainMenu(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 5;
    if (keyrow == 1 && x == -1) return 5;
    if (keyrow == 5 && x == 1) return 1;
    return keyrow + x;
}
int navigateLeaderboard(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 12;
    if (keyrow == 1 && x == -1) return 12;
    if (keyrow == 12 && x == 1) return 1;
    return keyrow + x;
}
int navigateSettingsMenu(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 3;
    if (keyrow == 1 && x == -1) return 3;
    if (keyrow == 3 && x == 1) return 1;
    return keyrow + x;
}
int navigateTutorialMenu(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 2;
    if (keyrow == 1 && x == -1) return 2;
    if (keyrow == 2 && x == 1) return 1;
    return keyrow + x;
}
int navigateOptionsList(int keyrow, int x) {
    if (keyrow == 0 && x == -1) return 4;
    if (keyrow == 1 && x == -1) return 4;
    if (keyrow == 4 && x == 1) return 1;
    return keyrow + x;
}
