#include <iostream>
#include <SDL.h>

using namespace std;

bool operator!=(SDL_Rect a, SDL_Rect b)
{
    if (a.x != b.x) return true;
    if (a.y != b.y) return true;
    if (a.w != b.w) return true;
    if (a.h != b.h) return true;
    return false;
}
