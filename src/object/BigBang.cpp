#include "BigBang.h"

BigBang::BigBang(int x_, int y_)
{
    x = x_;
    y = y_;
    frame = 0;
    w = Explosion_w / 4;
    h = Explosion_h / 4;
    int wi = 128;
    int hi = 128;
    int yi = 0;
    int dem = 0;
    for (int i = 0; i < 4; i++)
    {
        int xi = 0;
        for (int j = 0; j < 4; j++)
        {
            Explo[dem] = {xi , yi, wi, hi};
            xi += wi;
            dem++;
        }
        yi += hi;
    }
}

bool BigBang::render(SDL_Renderer *&gRenderer, LTexture &BB)
{
    if (frame > 15) return false;
    BB.render(gRenderer, x - w / 4, y - h / 4, &Explo[frame]);
    frame++;
    return true;
}


