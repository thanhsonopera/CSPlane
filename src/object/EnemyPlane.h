#ifndef EnemyPlane_h
#define EnemyPlane_h

#include <vector>
#include "EnemyBullet.h"
#include "Object.h"
#include "BigBang.h"

class Enemy: public Object
{
    int vx;
    bool alive;
    vector <EnemyBullet> bullet;
    vector <SDL_Rect> pos;
    LTexture status;
public:
    int hp;
    Enemy(int x_ , int y_, int diff);
    bool move1(SDL_Renderer *&gRenderer, int diff);
    void render(SDL_Renderer *&gRenderer, TTF_Font *&gFont, LTexture &EPlane, LTexture &Bullet);
    vector <SDL_Rect> getRect();
    void shift();
    bool alive1();
    void close();
    friend class Enemy2;
    friend void sinh(int sl1, int sl2, int sl3);
    friend void update();
    friend void reset();
};

#endif
