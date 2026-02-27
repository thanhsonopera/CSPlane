#include "EnemyBullet.h"
#include <iostream>

EnemyBullet::EnemyBullet(int x_, int y_, int diff)
{
    td = vt / ENEMY_BULLET_SPEED_DIV + diff / ENEMY_BULLET_DIFF_DIV;
    x = x_;
    y = y_;
    w = Bullet_w;
    h = Bullet_h;
    a = {x, y, w, h};
}

bool EnemyBullet::move1()
{
    if (y > Height) return false;
    y += td;
    shift();
    return true;
}

void EnemyBullet::shift()
{
    a.x = x;
    a.y = y;
}

SDL_Rect &EnemyBullet::getRect()
{
    return a;
}

