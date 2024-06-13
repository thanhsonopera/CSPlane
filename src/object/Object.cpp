#include "Object.h"

Object::Object(int x_, int y_)
{
    x = x_;
    y = y_;
}

void Object::render(SDL_Renderer *&gRenderer, LTexture &img)
{
    img.render(gRenderer, x, y);
}

