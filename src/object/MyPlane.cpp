#include "MyPlane.h"
#include "Constant.h"
#include <SDL.h>
#include <algorithm>

void MyPlane::loadfromfile(SDL_Renderer *&gRenderer, string path)
{
    img.loadfromfile(gRenderer, path.c_str());
    hp = PLANE_HP;
    alive = true;
    w = img.getWidth();
    h = img.getHeight();
    x = (Width - w) / 2;
    y = Height - h;  // screen Y

    pos.resize(6);

    pos[0].x = 0;
    pos[0].y = 0;
    pos[0].w = w * 11 / 40;
    pos[0].h = h * 17 / 77;

    pos[1].x = 0;
    pos[1].y = 0;
    pos[1].w = w * 1 / 10;
    pos[1].h = h * 28 / 77;

    pos[2].x = 0;
    pos[2].y = 0;
    pos[2].w = w * 1 / 4;
    pos[2].h = h - h * 15 / 77;

    pos[3].x = 0;
    pos[3].y = 0;
    pos[3].w = w * 1 / 10;
    pos[3].h = h * 28 / 77;

    pos[4].x = 0;
    pos[4].y = 0;
    pos[4].w = w * 11 / 40;
    pos[4].h = h * 17 / 77;

    pos[5].x = 0;
    pos[5].y = 0;
    pos[5].w = w * 5 / 12;
    pos[5].h = h * 15 / 77;

    shift();
}

void MyPlane::handle(SDL_Renderer *&gRenderer, SDL_Event &e, Uint32 currentTime)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            vy -= vt;
            break;
        case SDLK_DOWN:
            vy += vt;
            break;
        case SDLK_LEFT:
            vx -= vt;
            break;
        case SDLK_RIGHT:
            vx += vt;
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            vy += vt;
            break;
        case SDLK_DOWN:
            vy -= vt;
            break;
        case SDLK_LEFT:
            vx += vt;
            break;
        case SDLK_RIGHT:
            vx -= vt;
            break;
        }
    }
    // Clamp velocities to maximum allowed speed
    if (vx > maxSpeedX) vx = maxSpeedX;
    if (vx < -maxSpeedX) vx = -maxSpeedX;
    if (vy > maxSpeedY) vy = maxSpeedY;
    if (vy < -maxSpeedY) vy = -maxSpeedY;
}

void MyPlane::setVelocityFromKeys(const Uint8 *keys)
{
    vx = 0;
    vy = 0;
    if (keys[SDL_SCANCODE_LEFT])  vx -= vt;
    if (keys[SDL_SCANCODE_RIGHT]) vx += vt;
    if (keys[SDL_SCANCODE_UP])    vy -= vt;
    if (keys[SDL_SCANCODE_DOWN])  vy += vt;
    if (vx > maxSpeedX)  vx = maxSpeedX;
    if (vx < -maxSpeedX) vx = -maxSpeedX;
    if (vy > maxSpeedY)  vy = maxSpeedY;
    if (vy < -maxSpeedY) vy = -maxSpeedY;
}

void MyPlane::move1()
{
    if (alive == true)
    {
        x += vx;
        if (x < 0 || x + w > Width)  x -= vx;
        y += vy;
        if (y < 0 || y + h > Height) y -= vy;
        shift();
    }
    int i = 0;
    while (i < bullet.size())
    {
        if (bullet[i].move1() == false) {
            bullet.erase(bullet.begin() + i);
        }
        else i++;
    }
}

void MyPlane::updateBulletRecovery(Uint32 currentTime)
{
    // Initialize recovery timer
    if (recoveryTime == 0) {
        recoveryTime = currentTime;
        lastRegenTime = currentTime;
    }
    
    // Passive regeneration: 1 bullet every 2.5 seconds (up to max)
    if (currentTime - lastRegenTime >= PLANE_BULLET_REGEN_MS) {
        bulletCount = std::min(bulletCount + 1, maxBullets);
        lastRegenTime = currentTime;
    }
    
    // Every 30 seconds: recover 50% of max bullets AND increase max by 10
    if (currentTime - recoveryTime >= PLANE_RECOVERY_MS) {
        int recoveryAmount = maxBullets / 2;
        bulletCount = std::min(bulletCount + recoveryAmount, maxBullets);
        maxBullets += PLANE_RECOVERY_BONUS;
        recoveryTime = currentTime; // Reset recovery timer
    }
}

void MyPlane::fireBullet(int posX, int posY)
{
    if (bulletCount > 0) {
        MyBullet newBullet(posX, posY);
        bullet.push_back(newBullet);
        bulletCount--;
    }
}


void MyPlane::render(SDL_Renderer *&gRenderer, TTF_Font *&gFont, LTexture &Bullet)
{
    if (alive == true)
    {
        img.render(gRenderer, x, y);
        stringstream ss;
        ss.str("");
        ss << " HP:" << hp;
        status.loadfromrenderedtext(gRenderer, gFont, ss.str().c_str(), Color);
        status.render(gRenderer, x + (w - status.getWidth()) / 2, y + h);
    }
    for (int i = 0; i < bullet.size(); i++) bullet[i].render(gRenderer, Bullet);
}


void MyPlane::shift()
{
    int r = x;
    for (int i = 0; i < pos.size(); i++)
    {
        pos[i].x = r;
        pos[i].y = y + (h - pos[5].h - pos[i].h);
        r += pos[i].w;
    }
    pos[5].x = x + (w - pos[5].w) / 2;
    pos[5].y = y + (h - pos[5].h);
}

vector <SDL_Rect> MyPlane::getRect()
{
    return pos;
}

SDL_Rect MyPlane::getPos()
{
    SDL_Rect tam = {x, y, w, h};
    return tam;
}

bool MyPlane::alive1()
{
    return alive;
}

void MyPlane::close()
{
    bullet.clear();
    img.close();
    status.close();
}

int MyPlane::getVx()
{
    return vx;
}

int MyPlane::getVy()
{
    return vy;
}
