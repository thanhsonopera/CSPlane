#include "Play.h"

void reset()
{
    paused = false;
    score = 0;
    startTime = SDL_GetTicks();
    realTime = 0;
    pauseTime = 0;
    countTime = 0;
    continueTime = 0;
    background = {0, Level_Height - Height, Width, Height};
    Plane.x = (Width - Plane.w) / 2;
    Plane.y = Height - Plane.h;  // screen Y
    Plane.vx = 0;
    Plane.vy = 0;
    Plane.hp = PLANE_HP;
    Plane.alive = true;
    Plane.bulletCount = PLANE_MAX_BULLETS;
    Plane.maxBullets = PLANE_MAX_BULLETS;
    Plane.recoveryTime = 0;
    Plane.lastRegenTime = 0;
    Uint32 currentTime = SDL_GetTicks();
    
    Plane.ability1LastUse = currentTime - Plane.ability1Cooldown;
    Plane.ability2LastUse = currentTime - Plane.ability2Cooldown;

    Plane.bullet.clear();
    for (int i = 0; i < (int)EnemyPlane.size(); i++)
    {
        EnemyPlane[i].close();
    }
    for (int i = 0; i < (int)EnemyPlane2.size(); i++)
    {
        EnemyPlane2[i].close();
    }
    for (int i = 0; i < (int)Rks.size(); i++)
    {
        Rks[i].close();
    }
    EnemyPlane.clear();
    EnemyPlane2.clear();
    Rks.clear();
    HPBox.clear();
    Explosions.clear();
    Plane.status.close();
}

void close()
{
    BG1.close();
    Fl.close();
    MBullet.close();
    Bullet.close();
    EPlane.close();
    EPlane2.close();
    Rkt.close();
    BB.close();
    hp.close();
    Point.close();
    Time.close();
    BulletInfo.close();
    NoAmmoPopup.close();
    PressB.close();
    PressP.close();
    Plane.close();
    for (int i = 0; i < (int)EnemyPlane.size(); i++)
    {
        EnemyPlane[i].close();
    }
    for (int i = 0; i < (int)EnemyPlane2.size(); i++)
    {
        EnemyPlane2[i].close();
    }
    EnemyPlane.clear();
    EnemyPlane2.clear();
    HPBox.clear();
    Explosions.clear();
    Lasers1.clear();
    Lasers2.clear();
}
