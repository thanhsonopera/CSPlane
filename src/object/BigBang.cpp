#include "BigBang.h"
#include "../GameConfig.h"

BigBang::BigBang(int x_, int y_)
{
    x = x_;
    y = y_;
    frame = 0;
    w = Explosion_w / EXPLOSION_GRID;
    h = Explosion_h / EXPLOSION_GRID;
    int wi = EXPLOSION_FRAME_W;
    int hi = EXPLOSION_FRAME_H;
    int yi = 0;
    int dem = 0;
    for (int i = 0; i < EXPLOSION_GRID; i++)
    {
        int xi = 0;
        for (int j = 0; j < EXPLOSION_GRID; j++)
        {
            Explo[dem] = {xi, yi, wi, hi};
            xi += wi;
            dem++;
        }
        yi += hi;
    }
}

bool BigBang::render(SDL_Renderer *&gRenderer, LTexture &BB)
{
    if (frame > EXPLOSION_MAX_FRAME) return false;
    BB.render(gRenderer, x - w / 4, y - h / 4, &Explo[frame]);
    frame++;
    return true;
}


