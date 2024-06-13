#ifndef EnemyBullet_h
#define EnemyBullet_h

#include "Object.h"

class EnemyBullet: public Object
{
    SDL_Rect a;
    int td;
public:
    EnemyBullet(int x_ = 0, int y_ = 0, int diff = 0);
    bool move1();
    SDL_Rect &getRect();
    void shift();
};

#endif

