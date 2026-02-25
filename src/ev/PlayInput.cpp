#include "Play.h"

static void handlePauseToggle(const SDL_Event &e, Uint32 now) {
    if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_p || (e.key.keysym.sym == SDLK_b && paused == false))) {
        if (paused == true) {
            continueTime = now;
            paused = false;
        } else {
            pauseTime = countTime;
            paused = true;
        }
    }
}

void handleEvents(bool &quit, bool &fn, SDL_Event &e, SDL_Renderer *&gRenderer, Uint32 now) {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            close();
            quit = true;
        }
        if (Plane.alive1() == false) {
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) reset();
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b) {
                close();
                quit = true;
            }
        } else {
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b && paused == true) {
                close();
                quit = true;
            }
            handlePauseToggle(e, now);
            if (Plane.alive1() == true && paused == false) Plane.handle(gRenderer, e, now);
        }
    }
}

void handleContinuousInput(Uint32 now) {
    if (!(Plane.alive1() == true && paused == false)) return;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_SPACE]) {
        if (Plane.bulletCount > 0) {
            if (now - Plane.lastFireTime >= Plane.fireDelay) {
                Plane.fireBullet(Plane.x + (Plane.w - Bullet_w) / 2, Plane.y);
                Plane.lastFireTime = now;
            }
        } else {
            Plane.lastNoAmmoTime = now;
        }
    }
    bool xKeyPressed = keys[SDL_SCANCODE_X];
    if (xKeyPressed && !lastXKeyPressed && (now - Plane.ability1LastUse >= Plane.ability1Cooldown)) {
        int laserDamage = LASER1_DAMAGE_BASE + (realTime / 60000) * LASER1_DAMAGE_PER_MIN;
        Laser newLaser(Plane.x + Plane.w/2, Plane.y - LASER_OFFSET_Y, laserDamage, LASER1_W, LASER1_H, LASER_DURATION_MS, countTime, Plane.getVx(), Plane.getVy());
        Lasers1.push_back(newLaser);
        Plane.ability1LastUse = now;
    }
    lastXKeyPressed = xKeyPressed;

    bool cKeyPressed = keys[SDL_SCANCODE_C];
    if (cKeyPressed && !lastCKeyPressed && (now - Plane.ability2LastUse >= Plane.ability2Cooldown)) {
        int laserDamage = LASER2_DAMAGE_BASE + (realTime / 60000) * LASER2_DAMAGE_PER_MIN;
        Laser laser1(Plane.x - LASER_SPREAD, Plane.y - LASER_OFFSET_Y, laserDamage, LASER2_W, LASER2_H, LASER_DURATION_MS, countTime, Plane.getVx(), Plane.getVy());
        Lasers2.push_back(laser1);
        Laser laser2(Plane.x + Plane.w/2, Plane.y - LASER_OFFSET_Y, laserDamage, LASER1_W, LASER2_H, LASER_DURATION_MS, countTime, Plane.getVx(), Plane.getVy());
        Lasers2.push_back(laser2);
        Laser laser3(Plane.x + Plane.w + LASER_SPREAD, Plane.y - LASER_OFFSET_Y, laserDamage, LASER2_W, LASER2_H, LASER_DURATION_MS, countTime, Plane.getVx(), Plane.getVy());
        Lasers2.push_back(laser3);
        Plane.ability2LastUse = now;
    }
    lastCKeyPressed = cKeyPressed;
}
