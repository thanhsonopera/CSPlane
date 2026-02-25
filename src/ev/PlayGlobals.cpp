#include "Play.h"
#include <vector>

// Global definitions
LTexture BG1;
LTexture Fl;
LTexture MBullet;
LTexture Bullet;
LTexture EPlane;
LTexture EPlane2;
LTexture Rkt;
LTexture BB;
LTexture hp;
LTexture Point;
LTexture Time;
LTexture PressP;
LTexture PressB;
LTexture Die;
LTexture Result;
LTexture PlayAgain;
LTexture BulletInfo;
LTexture NoAmmoPopup;

SDL_Rect background;
MyPlane Plane;
std::vector<HP> HPBox;
std::vector<Enemy> EnemyPlane;
std::vector<Enemy2> EnemyPlane2;
std::vector<Rocket> Rks;
std::vector<BigBang> Explosions;
std::vector<Laser> Lasers1; // Single laser ability
std::vector<Laser> Lasers2; // Triple laser ability
Uint32 timing = 0;
int score = 0;
bool paused = false;
Uint32 countTime = 0;
Uint32 startTime = 0;
Uint32 realTime = 0;
Uint32 pauseTime = 0;
Uint32 continueTime = 0;
bool lastXKeyPressed = false;
bool lastCKeyPressed = false;
