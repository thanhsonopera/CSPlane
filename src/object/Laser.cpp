#include "Constant.h"
#include "Laser.h"

Laser::Laser(int sx, int sy, int dame, int w, int h, Uint32 dur, Uint32 currentTime, int svx, int svy)
    : x(sx), y(sy), damage(dame), width(w), height(h), duration(dur), spawnTime(currentTime), vx(svx), vy(svy)
{
}

bool Laser::isActive(Uint32 currentTime)
{
    return (currentTime - spawnTime) < duration;
}

bool Laser::checkCollision(SDL_Rect enemyRect)
{
    SDL_Rect laserRect = {x - width/2, y - height/2, width, height};
    return SDL_HasIntersection(&laserRect, &enemyRect);
}

void Laser::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, LASER_COLOR_R, LASER_COLOR_G, LASER_COLOR_B, 255);
    SDL_Rect rect = {x - width/2, y - height/2, width, height};
    SDL_RenderFillRect(renderer, &rect);
}

int Laser::getDamage()
{
    return damage;
}

void Laser::move()
{
    x += vx;
    y += vy;
}

void Laser::moveBy(int dx, int dy)
{
    x += dx;
    y += dy;
}
