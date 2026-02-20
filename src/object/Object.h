#ifndef Object_h
#define Object_h

#include "LTexture.h"

class Object
{
public:
    int x;
    int y;
    int w;
    int h;
    static const int vt = 8;
    Object(int x_ = 0, int y_ = 0);
    void render(SDL_Renderer *&gRenderer, LTexture &img);
};

#endif
