#include "Rocket.h"

Rocket::Rocket(int x_, int y_, int diff)
{
    x = x_;
    y = y_;
    w = Rocket_w;
    h = Rocket_h;
    hp = 100;
    vy = vt / 2 + diff / 60000 * 2;
}

bool Rocket::move1()
{
    if (y > Height) return false;
    if (hp <= 0) return false;
    y += vy;
    return true;
}

void Rocket::render(SDL_Renderer *&gRenderer, TTF_Font *&gFont, LTexture &Rkt)
{
    if (y < 0)
    {
        SDL_Rect tam = {0, abs(y), w, h + y};
        Rkt.render(gRenderer, x, 0, &tam);
    }
    else
    {
        Rkt.render(gRenderer, x, y);
    }
    stringstream ss;
    ss.str("");
    ss << " HP:" << hp;
    status.loadfromrenderedtext(gRenderer, gFont, ss.str().c_str(), Color);
    status.render(gRenderer, x + (w - status.getWidth()) / 2, y - status.getHeight());
}

SDL_Rect Rocket::getPos()
{
    SDL_Rect tam = {x, y, w, h};
    return tam;
}

void Rocket::close()
{
    status.close();
}
