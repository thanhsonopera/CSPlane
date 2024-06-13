#ifndef Rocket_H
#define Rocket_H

#include <sstream>
#include <stdlib.h>
#include "Object.h"
#include "Constant.h"

class Rocket: public Object
{
    int vy;
    LTexture status;
public:
    int hp;
    Rocket(int x_, int y_, int diff);
    bool move1();
    void render(SDL_Renderer *&gRenderer, TTF_Font *&gFont, LTexture &Rkt);
    SDL_Rect getPos();
    void close();
    friend void sinh(int sl1, int sl2);
    friend void update();
};

#endif
