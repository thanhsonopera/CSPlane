#include "CheckCollision.h"

bool CheckCollision(const SDL_Rect &a, const SDL_Rect &b)
{
    if (a.y > b.y + b.h) return false;
    if (a.y + a.h < b.y) return false;
    if (a.x > b.x + b.w) return false;
    if (a.x + a.w < b.x) return false;
    return true;
}
