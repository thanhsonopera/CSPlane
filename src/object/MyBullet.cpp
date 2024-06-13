#include "MyBullet.h"

MyBullet::MyBullet(int x_, int y_)
{
    x = x_;
    y = y_;
    w = Bullet_w;
    h = Bullet_h;
    a = {x, y, w, h};
}

bool MyBullet::move1()
{
    if (y < 0) return false;
    y -= vt / 2;
    shift();
    return true;
}

SDL_Rect &MyBullet::getRect()
{
    return a;
}

void MyBullet::shift()
{
    a.x = x;
    a.y = y;
}
