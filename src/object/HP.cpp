#include "HP.h"

HP::HP(int x_, int y_)
{
    x = x_;
    y = y_;
    w = hp_w;
    h = hp_h;
}

bool HP::move1()
{
    if (y > Height) return false;
    y += vt / 4;
    return true;
}
