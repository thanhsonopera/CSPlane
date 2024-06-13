#ifndef MyBullet_h
#define MyBullet_h

#include "Object.h"

class MyBullet: public Object
{
    SDL_Rect a;
public:
    MyBullet(int x_ = 0, int y_ = 0);
    bool move1();
    SDL_Rect &getRect();
    void shift();
};

#endif
