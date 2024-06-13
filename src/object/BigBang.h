#ifndef BigBang_h
#define BigBang_h

#include "LTexture.h"

class BigBang
{
    int x;
    int y;
    int w;
    int h;
    int frame;
    SDL_Rect Explo[16];
    LTexture clip;
public:
    BigBang(int x_, int y_);
    bool render(SDL_Renderer *&gRenderer, LTexture &BB);
};

#endif
