#ifndef Laser_h
#define Laser_h

#include <SDL2/SDL.h>
#include "Constant.h"

class Laser
{
private:
    int x, y;
    int damage;
    int width;
    int height;
    Uint32 spawnTime;
    Uint32 duration; 
    int vx; // horizontal velocity (pixels per frame)
    int vy; // vertical velocity (pixels per frame)
    
public:
    Laser(int sx, int sy, int dame, int w, int h, Uint32 dur, Uint32 currentTime, int svx = 0, int svy = 0);
    void move();
    void moveBy(int dx, int dy);
    
    bool isActive(Uint32 currentTime);
    bool checkCollision(SDL_Rect enemyRect);
    void render(SDL_Renderer *renderer);
    int getDamage();
    
    friend void update();
};

#endif
