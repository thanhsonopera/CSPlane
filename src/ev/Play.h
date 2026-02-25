#ifndef Play_h
#define Play_h

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <utility>


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
#include "../object/Laser.h"

extern LTexture BG1;
extern LTexture Fl;
extern LTexture MBullet;
extern LTexture Bullet;
extern LTexture EPlane;
extern LTexture EPlane2;
extern LTexture Rkt;
extern LTexture BB;
extern LTexture hp;
extern LTexture Point;
extern LTexture Time;
extern LTexture PressP;
extern LTexture PressB;
extern LTexture Die;
extern LTexture Result;
extern LTexture PlayAgain;
extern LTexture BulletInfo;
extern LTexture NoAmmoPopup;

extern SDL_Rect background;
extern MyPlane Plane;
extern std::vector<HP> HPBox;
extern std::vector<Enemy> EnemyPlane;
extern std::vector<Enemy2> EnemyPlane2;
extern std::vector<Rocket> Rks;
extern std::vector<BigBang> Explosions;
extern std::vector<Laser> Lasers1; // Single laser ability
extern std::vector<Laser> Lasers2; // Triple laser ability
extern Uint32 timing;
extern int score;
extern bool paused;
extern Uint32 countTime;
extern Uint32 startTime;
extern Uint32 realTime;
extern Uint32 pauseTime;
extern Uint32 continueTime;
extern bool lastXKeyPressed;
extern bool lastCKeyPressed;

void sinh(int sl1, int sl2, int sl3);
void update();
void Exp(SDL_Renderer *&gRenderer);
void loadmedia(SDL_Renderer *&gRenderer, TTF_Font *&gFont, TTF_Font *&pFont);
void loadbg(int &check_background, SDL_Renderer *&gRenderer);
void xuly(int &check_background, SDL_Window *&gWindow, SDL_Renderer *&gRenderer, TTF_Font *&gFont, TTF_Font *&pFont);

// Refactored helpers to keep components small
void handleEvents(bool &quit, bool &fn, SDL_Event &e, SDL_Renderer *&gRenderer, Uint32 now);
void handleContinuousInput(Uint32 now);
void renderBackgroundAndFinishLine(bool &fn, SDL_Renderer *&gRenderer);
void updateHUD(SDL_Renderer *&gRenderer, TTF_Font *&gFont);
void updateLasersAndCollisions();
void updateWorld(SDL_Renderer *&gRenderer);
void renderGame(SDL_Renderer *&gRenderer, TTF_Font *&gFont, TTF_Font *&pFont);
void renderDeathScreen(SDL_Renderer *&gRenderer, TTF_Font *&pFont);

// Comparator for results sorting
bool dk(std::pair<int, int> a, std::pair<int, int> b);

// Lifecycle
void reset();
void close();

#endif
