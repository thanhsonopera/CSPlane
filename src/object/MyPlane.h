#ifndef MyPlane_h
#define MyPlane_h

#include <stdio.h>
#include <vector>
#include <sstream>
// #include "Constant.h"
#include "Object.h"
#include "MyBullet.h"
#include "BigBang.h"
#include "../GameConfig.h"

class MyPlane: public Object
{
    int vx = 0;
    int vy = 0;
    int maxSpeedX = PLANE_MAX_SPEED_X;
    int maxSpeedY = PLANE_MAX_SPEED_Y;
    vector <SDL_Rect> pos;
    bool alive;
    LTexture img;
    LTexture status;
public:
    vector <MyBullet> bullet;
    int maxBullets = PLANE_MAX_BULLETS;
    int bulletCount = PLANE_MAX_BULLETS;
    Uint32 lastFireTime = 0;
    Uint32 fireDelay = PLANE_FIRE_DELAY_MS;
    Uint32 recoveryTime = 0;
    Uint32 lastRegenTime = 0;
    int hp;
    Uint32 lastNoAmmoTime = 0;
    
    // Ability 1: Single laser - 20s cooldown, range 100, 50 damage (+10 per minute)
    Uint32 ability1LastUse = 0;
    const Uint32 ability1Cooldown = PLANE_ABILITY1_CD_MS;
    Uint32 ability2LastUse = 0;
    const Uint32 ability2Cooldown = PLANE_ABILITY2_CD_MS;
    
    void loadfromfile(SDL_Renderer *&gRenderer, string path);
    void handle(SDL_Renderer *&gRenderer, SDL_Event &e, Uint32 currentTime);
    /// Set vx,vy from current key state so plane only moves when keys are held (no drift)
    void setVelocityFromKeys(const Uint8 *keys);
    void move1();
    void render(SDL_Renderer *&gRenderer, TTF_Font *&gFont, LTexture &Bullet);
    vector <SDL_Rect> getRect();
    SDL_Rect getPos();
    void shift();
    bool alive1();
    void close();
    void updateBulletRecovery(Uint32 currentTime);
    void fireBullet(int posX, int posY);
    int getVx();
    int getVy();
    friend class HP;
    friend void sinh();
    friend void update();
    friend void reset();
};

#endif
