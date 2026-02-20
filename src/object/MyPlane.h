#ifndef MyPlane_h
#define MyPlane_h

#include <stdio.h>
#include <vector>
#include <sstream>
#include "Object.h"
#include "MyBullet.h"
#include "BigBang.h"

class MyPlane: public Object
{
    int vx = 0;
    int vy = 0;
    vector <SDL_Rect> pos;
    bool alive;
    LTexture img;
    LTexture status;
public:
    vector <MyBullet> bullet;
    int maxBullets = 20;
    int bulletCount = 20;
    Uint32 lastFireTime = 0;
    Uint32 fireDelay = 100;
    Uint32 recoveryTime = 0;
    Uint32 lastRegenTime = 0;
    int regenPerSecond = 2;
    int hp;
    void loadfromfile(SDL_Renderer *&gRenderer, string path);
    void handle(SDL_Renderer *&gRenderer, SDL_Event &e, Uint32 currentTime);
    void move1();
    void render(SDL_Renderer *&gRenderer, TTF_Font *&gFont, LTexture &Bullet);
    vector <SDL_Rect> getRect();
    SDL_Rect getPos();
    void shift();
    bool alive1();
    void close();
    void updateBulletRecovery(Uint32 currentTime);
    void fireBullet(int posX, int posY);
    friend class HP;
    friend void sinh();
    friend void update();
    friend void reset();
};

#endif
