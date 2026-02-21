#include <iostream>
#include <algorithm>
#include <fstream>

#include "Play.h"
#include "Menu.h"
#include "Paths.h"
#include "../object/Laser.h"

// Global variable

LTexture BG1;
LTexture Fl;
LTexture MBullet;
LTexture Bullet;
LTexture EPlane;
LTexture EPlane2;
LTexture Rkt;
LTexture BB;
LTexture hp;
LTexture Point;
LTexture Time;
LTexture PressP;
LTexture PressB;
LTexture Die;
LTexture Result;
LTexture PlayAgain;
LTexture BulletInfo;
LTexture NoAmmoPopup;

SDL_Rect background;
MyPlane Plane;
vector <HP> HPBox;
vector <Enemy> EnemyPlane;
vector <Enemy2> EnemyPlane2;
vector <Rocket> Rks;
vector <BigBang> Explosions;
vector <Laser> Lasers1; // Single laser ability
vector <Laser> Lasers2; // Triple laser ability
Uint32 timing = 0;
int score;
bool paused;
Uint32 countTime = 0;
Uint32 startTime = 0;
Uint32 realTime = 0;
Uint32 pauseTime = 0;
Uint32 continueTime = 0;
bool lastXKeyPressed = false;
bool lastCKeyPressed = false;


//Random EnemyPlane

void sinh(int sl1, int sl2, int sl3)
{
    int x1 = min1 + rand() % (max1 - min1);
    if (x1 == 5 && EnemyPlane.size() < min(sl1, 5))
    {
        int y = 0;
        while (true)
        {
            y = 0 + rand() % (Width - Plane_w);
            bool ok = true;
            for (int i = 0; i < EnemyPlane.size(); i++)
                if (EnemyPlane[i].alive1() == true)
                {
                    int a = EnemyPlane[i].x;
                    int b = Plane_w;
                    if (y >= a - b && y <= a + b)
                    {
                        ok = false;
                        break;
                    }
                }
            for (int i = 0; i < EnemyPlane2.size(); i++)
                if (EnemyPlane2[i].alive1() == true)
                {
                    int a = EnemyPlane2[i].x;
                    int b = Plane2_w;
                    int c = Plane_w;
                    if (y >= a - c && y <= a + b)
                    {
                        ok = false;
                        break;
                    }
                }
            if (ok == true) break;
        }
        Enemy tam(y, 0, realTime);
        EnemyPlane.push_back(tam);
    }

    int x2 = min1 + rand() % (max1 - min1);
    if (x2 == 10 && EnemyPlane2.size() < min(sl2, 3))
    {
        int y = 0;
        while (true)
        {
            y = 0 + rand() % (Width - Plane2_w);
            bool ok = true;
            for (int i = 0; i < EnemyPlane.size(); i++)
                if (EnemyPlane[i].alive1() == true)
                {
                    int a = EnemyPlane[i].x;
                    int b = Plane_w;
                    int c = Plane2_w;
                    if (y >= a - c && y <= a + b)
                    {
                        ok = false;
                        break;
                    }
                }
            for (int i = 0; i < EnemyPlane2.size(); i++)
                if (EnemyPlane2[i].alive1() == true)
                {
                    int a = EnemyPlane2[i].x;
                    int b = Plane2_w;
                    if (y >= a - b && y <= a + b)
                    {
                        ok = false;
                        break;
                    }
                }
            if (ok == true) break;
        }
        Enemy2 tam(y, 0, realTime);
        EnemyPlane2.push_back(tam);
    }

    int x3 = min1 + rand() % (max1 + 50 - min1);
    if (x3 == 15 && Rks.size() < min(sl3, 3))
    {
        SDL_Rect vt = Plane.getPos();
        Rocket tam(vt.x + (vt.w - Rocket_w) / 2, -Rocket_h, realTime);
        Rks.push_back(tam);
    }
}

//Update Objects

void update()
{
    //May bay dong minh va cham may bay dich
    vector <SDL_Rect> tam1 = Plane.getRect();
    for (int i = 0; i < EnemyPlane.size(); i++)
        if (EnemyPlane[i].alive1() == true)
        {
            vector <SDL_Rect> tam2 = EnemyPlane[i].getRect();
            for (int j = 0; j < tam1.size(); j++)
            {
                bool ok = true;
                for (int k = 0; k < tam2.size(); k++)
                    if (CheckCollision(tam1[j], tam2[k]) == true)
                    {
                        Plane.hp -= 30;
                        EnemyPlane[i].hp = 0;
                        ok = false;
                        break;
                    }
                if (ok == false) break;
            }
        }

    for (int i = 0; i < EnemyPlane2.size(); i++)
        if (EnemyPlane2[i].alive1() == true)
        {
            vector <SDL_Rect> tam2 = EnemyPlane2[i].getRect();
            for (int j = 0; j < tam1.size(); j++)
            {
                bool ok = true;
                for (int k = 0; k < tam2.size(); k++)
                    if (CheckCollision(tam1[j], tam2[k]) == true)
                    {
                        Plane.hp -= 50;
                        EnemyPlane2[i].hp = 0;
                        ok = false;
                        break;
                    }
                if (ok == false) break;
            }
        }

    //May bay dich va cham may bay dich

    for (int i = 0; i < EnemyPlane.size(); i++)
        if (EnemyPlane[i].alive1() == true)
        {
            SDL_Rect tam2 = {EnemyPlane[i].x, EnemyPlane[i].y, EnemyPlane[i].w, EnemyPlane[i].h};
            for (int j = i + 1; j < EnemyPlane.size(); j++)
                if (EnemyPlane[j].alive1() == true)
                {
                    SDL_Rect tam3 = {EnemyPlane[j].x, EnemyPlane[j].y, EnemyPlane[j].w, EnemyPlane[j].h};
                    if (CheckCollision(tam2, tam3) == true)
                    {
                        EnemyPlane[i].vx = -EnemyPlane[i].vx;
                        EnemyPlane[j].vx = -EnemyPlane[j].vx;
                    }
                }
        }

    for (int i = 0; i < EnemyPlane2.size(); i++)
        if (EnemyPlane2[i].alive1() == true)
        {
            SDL_Rect tam2 = {EnemyPlane2[i].x, EnemyPlane2[i].y - EnemyPlane2[i].status.getHeight(), EnemyPlane2[i].w, EnemyPlane2[i].h + EnemyPlane2[i].status.getHeight()};
            for (int j = i + 1; j < EnemyPlane2.size(); j++)
                if (EnemyPlane2[j].alive1() == true)
                {
                    SDL_Rect tam3 = {EnemyPlane2[j].x, EnemyPlane2[j].y - EnemyPlane2[j].status.getHeight(), EnemyPlane2[j].w, EnemyPlane2[j].h + EnemyPlane2[j].status.getHeight()};
                    if (CheckCollision(tam2, tam3) == true)
                    {
                        EnemyPlane2[i].vx = -EnemyPlane2[i].vx;
                        EnemyPlane2[j].vx = -EnemyPlane2[j].vx;
                    }
                }
        }

    for (int i = 0; i < EnemyPlane.size(); i++)
        if (EnemyPlane[i].alive1() == true)
        {
            SDL_Rect tam2 = {EnemyPlane[i].x, EnemyPlane[i].y, EnemyPlane[i].w, EnemyPlane[i].h};
            for (int j = 0; j < EnemyPlane2.size(); j++)
                if (EnemyPlane2[j].alive1() == true)
                {
                    SDL_Rect tam3 = {EnemyPlane2[j].x, EnemyPlane2[j].y - EnemyPlane2[j].status.getHeight(), EnemyPlane2[j].w, EnemyPlane2[j].h + EnemyPlane2[j].status.getHeight()};
                    if (CheckCollision(tam2, tam3) == true)
                    {
                        EnemyPlane[i].vx = -EnemyPlane[i].vx;
                        EnemyPlane2[j].vx = -EnemyPlane2[j].vx;
                    }
                }
        }

    //Dan va cham may bay dich

    int i = 0;

    while (i < Plane.bullet.size())
    {
        SDL_Rect tam2 = Plane.bullet[i].getRect();
        bool ok = true;
        for (int j = 0; j < EnemyPlane.size(); j++)
            if (EnemyPlane[j].alive1() == true)
            {
                vector <SDL_Rect> tam3 = EnemyPlane[j].getRect();
                for (int k = 0; k < tam3.size(); k++)
                    if (CheckCollision(tam2, tam3[k]) == true)
                    {
                        EnemyPlane[j].hp -= 10;
                        Plane.bullet.erase(Plane.bullet.begin() + i);
                        ok = false;
                        break;
                    }
                if (ok == false) break;
            }
        if (ok == true)
        {
            for (int j = 0; j < EnemyPlane2.size(); j++)
                if (EnemyPlane2[j].alive1() == true)
                {
                    vector <SDL_Rect> tam3 = EnemyPlane2[j].getRect();
                    for (int k = 0; k < tam3.size(); k++)
                        if (CheckCollision(tam2, tam3[k]) == true)
                        {
                            EnemyPlane2[j].hp -= 10;
                            Plane.bullet.erase(Plane.bullet.begin() + i);
                            ok = false;
                            break;
                        }
                    if (ok == false) break;
                }
        }
        if (ok == true) i++;
    }

    //Dan va cham ten lua

    i = 0;
    while (i < Plane.bullet.size())
    {
        SDL_Rect tam2 = Plane.bullet[i].getRect();
        bool ok = true;
        for (int j = 0; j < Rks.size(); j++)
        {
            SDL_Rect tam3 = Rks[j].getPos();
            if (CheckCollision(tam2, tam3) == true)
            {
                Rks[j].hp -= 20;
                Plane.bullet.erase(Plane.bullet.begin() + i);
                ok = false;
            }
            if (ok == false) break;
        }
        if (ok == true) i++;
    }


    //Dan va cham may bay dong minh

    for (int j = 0; j < EnemyPlane.size(); j++)
    {
        int k = 0;
        while (k < EnemyPlane[j].bullet.size())
        {
            bool ok = true;
            SDL_Rect tam2 = EnemyPlane[j].bullet[k].getRect();
            for (int e = 0; e < tam1.size(); e++)
                if (CheckCollision(tam2, tam1[e]) == true)
                {
                    Plane.hp -= 10;
                    EnemyPlane[j].bullet.erase(EnemyPlane[j].bullet.begin() + k);
                    ok = false;
                    break;
                }
            if (ok == true) k++;
        }
    }

    for (int j = 0; j < EnemyPlane2.size(); j++)
    {
        int k = 0;
        while (k < EnemyPlane2[j].bullet.size())
        {
            bool ok = true;
            SDL_Rect tam2 = EnemyPlane2[j].bullet[k].getRect();
            for (int e = 0; e < tam1.size(); e++)
                if (CheckCollision(tam2, tam1[e]) == true)
                {
                    Plane.hp -= 10;
                    EnemyPlane2[j].bullet.erase(EnemyPlane2[j].bullet.begin() + k);
                    ok = false;
                    break;
                }
            if (ok == true) k++;
        }
    }

    //Ten lua va cham may bay dong minh
    for (int j = 0; j < Rks.size(); j++)
    {
        vector <SDL_Rect> tam2 = Plane.getRect();
        SDL_Rect tam3 = Rks[j].getPos();
        for (int e = 0; e < tam2.size(); e++)
            if (CheckCollision(tam3, tam2[e]) == true)
            {
                Plane.hp -= 50;
                Rks[j].hp = 0;
                break;
            }
    }

    //Xu li HP
    i = 0;
    while (i < HPBox.size())
    {
        bool ok = true;
        SDL_Rect tam2 = {HPBox[i].x, HPBox[i].y, HPBox[i].w, HPBox[i].h};
        SDL_Rect tam3 = {Plane.x, Plane.y, Plane.w, Plane.h};
        if (CheckCollision(tam2, tam3) == true)
        {
            Plane.hp += 20;
            HPBox.erase(HPBox.begin() + i);
            ok = false;
        }
        if (ok == true) i++;
    }

    //Cac vu no

    if (Plane.alive1() == true)
    {
        if (Plane.hp <= 0)
        {
            Plane.alive = false;
            BigBang k(Plane.x, Plane.y);
            Explosions.push_back(k);
        }
    }

    for (int j = 0; j < EnemyPlane.size(); j++)
        if (EnemyPlane[j].alive1() == true)
        {
            if (EnemyPlane[j].hp <= 0)
            {
                EnemyPlane[j].alive = false;
                score += 30;
                BigBang k(EnemyPlane[j].x, EnemyPlane[j].y);
                Explosions.push_back(k);
                int t1 = rand() % 15;
                if (t1 == 10)
                {
                    HP t2(EnemyPlane[j].x, EnemyPlane[j].y);
                    HPBox.push_back(t2);
                }
            }
        }
    for (int j = 0; j < EnemyPlane2.size(); j++)
        if (EnemyPlane2[j].alive1() == true)
        {
            if (EnemyPlane2[j].hp <= 0)
            {
                EnemyPlane2[j].alive = false;
                score += 50;
                BigBang k(EnemyPlane2[j].x, EnemyPlane2[j].y);
                Explosions.push_back(k);
                int t1 = rand() % 15;
                if (t1 == 10)
                {
                    HP t2(EnemyPlane2[j].x, EnemyPlane2[j].y);
                    HPBox.push_back(t2);
                }
            }
        }
    for (int j = 0; j < Rks.size(); j++)
        if (Rks[j].hp <= 0)
    {
        BigBang k(Rks[j].x, Rks[j].y);
        Explosions.push_back(k);
    }
}

//Explosions

void Exp(SDL_Renderer *&gRenderer)
{
    int i = 0;
    while (i < Explosions.size())
    {
        if (Explosions[i].render(gRenderer, BB) == false) Explosions.erase(Explosions.begin() + i);
        else i++;
    }
}


//reset

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
    Plane.hp = 100;
    Plane.alive = true;
    Plane.bulletCount = 20;
    Plane.maxBullets = 20;
    Plane.recoveryTime = 0;
    Plane.lastRegenTime = 0;
    Uint32 currentTime = SDL_GetTicks();
    
    Plane.ability1LastUse = currentTime - Plane.ability1Cooldown;
    Plane.ability2LastUse = currentTime - Plane.ability2Cooldown;

    Plane.bullet.clear();
    for (int i = 0; i < EnemyPlane.size(); i++)
    {
        EnemyPlane[i].close();
    }
    for (int i = 0; i < EnemyPlane2.size(); i++)
    {
        EnemyPlane2[i].close();
    }
    for (int i = 0; i < Rks.size(); i++)
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

//close

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
    for (int i = 0; i < EnemyPlane.size(); i++)
    {
        EnemyPlane[i].close();
    }
    for (int i = 0; i < EnemyPlane2.size(); i++)
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

//Loadmedia

void loadmedia(SDL_Renderer *&gRenderer, TTF_Font *&gFont, TTF_Font *&pFont)
{
    gFont = TTF_OpenFont("font/VAPTIMN.TTF", 13);
    if (!gFont) gFont = TTF_OpenFont("VAPTIMN.TTF", 13);
    pFont = TTF_OpenFont("font/VAVOBI.TTF", 20);
    if (!pFont) pFont = TTF_OpenFont("VAVOBI.TTF", 20);
    Fl.loadfromfile(gRenderer, imgUI("FinishLine.png"));
    Plane.loadfromfile(gRenderer, imgPlanes("MyPlane.png"));
    MBullet.loadfromfile(gRenderer, imgBullets("MyBullet.png"));
    Bullet.loadfromfile(gRenderer, imgBullets("Bullet.png"));
    EPlane.loadfromfile(gRenderer, imgPlanes("EnemyPlane.png"));
    EPlane2.loadfromfile(gRenderer, imgPlanes("EnemyPlane2.png"));
    Rkt.loadfromfile(gRenderer, imgRockets("Rocket.png"));
    BB.loadfromfile(gRenderer, imgEffects("Explosion.png"));
    hp.loadfromfile(gRenderer, imgUI("HP.png"));
    PressP.loadfromrenderedtext(gRenderer, pFont, "Press P to Continue", Color);
    PressB.loadfromrenderedtext(gRenderer, pFont, "Press B to Back to Menu", Color);
    Die.loadfromrenderedtext(gRenderer, pFont, "You died!", Color);
    PlayAgain.loadfromrenderedtext(gRenderer, pFont, "Press Enter to Play again", Color);
}

//load background

void loadbg(int &check_background, SDL_Renderer *&gRenderer)
{
    if (check_background == 1) BG1.loadfromfile(gRenderer, imgBg("Jungle.png"));
    if (check_background == 2) BG1.loadfromfile(gRenderer, imgBg("ocean.png"));
    if (check_background == 3) BG1.loadfromfile(gRenderer, imgBg("galaxy.png"));
}

//point sort

bool dk(pair<int, int> a, pair<int, int> b)
{
    if (a.first == b.first)
    {
        if (a.second > b.second) return false;
        return true;
    }
    if (a.first < b.first) return false;
    return true;
}

void xuly(int &check_background, SDL_Window *&gWindow, SDL_Renderer *&gRenderer, TTF_Font *&gFont, TTF_Font *&pFont)
{
    reset();
    loadmedia(gRenderer, gFont, pFont);
    loadbg(check_background, gRenderer);
    bool quit = false;
    bool fn = false;
    SDL_Event e;
    background = {0, Level_Height - Height, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    while (!quit)
    {
        Uint32 tam1 = SDL_GetTicks();
        
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                close();
                quit = true;
            }
            if (Plane.alive1() == false)
            {
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) reset();
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b)
                {   
                    
                    close();
                    quit = true;
                  
                }
            }
            else
            {   
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_b && paused == true)
                {
                    close();
                    quit = true;
                }

                if (e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_p || (e.key.keysym.sym == SDLK_b && paused  == false)))
                {   
                 
                    if (paused == true)
                    {
                        continueTime = SDL_GetTicks();
                        paused = false;
                      
                    }
                    else
                    {
                        pauseTime = countTime;
                        paused = true;

                    }
                    
                }
                else if (Plane.alive1() == true && paused == false) Plane.handle(gRenderer, e, tam1);
            }
        }

        // Handle continuous SPACE key press for firing
        if (Plane.alive1() == true && paused == false)
        {
            const Uint8 *keys = SDL_GetKeyboardState(NULL);
            if (keys[SDL_SCANCODE_SPACE])
            {
                if (Plane.bulletCount > 0)
                {
                    if (tam1 - Plane.lastFireTime >= Plane.fireDelay)
                    {
                        Plane.fireBullet(Plane.x + (Plane.w - Bullet_w) / 2, Plane.y);
                        Plane.lastFireTime = tam1;
                    }
                }
                else
                {
                    // No ammo - show popup
                    Plane.lastNoAmmoTime = tam1;
                }
            }
            
            // Ability 1: X key - Single laser (20s cooldown, 1s duration)
            bool xKeyPressed = keys[SDL_SCANCODE_X];
            if (xKeyPressed && !lastXKeyPressed && (tam1 - Plane.ability1LastUse >= Plane.ability1Cooldown))
            {
                int laserDamage = 50 + (realTime / 60000) * 10; // +10 damage per minute
                Laser newLaser(Plane.x + Plane.w/2, Plane.y - 55, laserDamage, 10, 80, 500, countTime, Plane.getVx(), Plane.getVy());
                Lasers1.push_back(newLaser);
                Plane.ability1LastUse = tam1;
            }
            lastXKeyPressed = xKeyPressed;
            
            // Ability 2: C key - Triple laser (30s cooldown, 1s duration)
            bool cKeyPressed = keys[SDL_SCANCODE_C];
            if (cKeyPressed && !lastCKeyPressed && (tam1 - Plane.ability2LastUse >= Plane.ability2Cooldown))
            {
                int laserDamage = 30 + (realTime / 60000) * 20; // +20 damage per minute
                // Left laser (spread further apart)
                Laser laser1(Plane.x - 15, Plane.y - 55, laserDamage, 8, 100, 500, countTime, Plane.getVx(), Plane.getVy());
                Lasers2.push_back(laser1);
                // Center laser
                Laser laser2(Plane.x + Plane.w/2, Plane.y - 55, laserDamage, 10, 100, 500, countTime, Plane.getVx(), Plane.getVy());
                Lasers2.push_back(laser2);
                // Right laser
                Laser laser3(Plane.x + Plane.w + 15, Plane.y - 55, laserDamage, 8, 100, 500, countTime, Plane.getVx(), Plane.getVy());
                Lasers2.push_back(laser3);
                Plane.ability2LastUse = tam1;
            }
            lastCKeyPressed = cKeyPressed;
        }

        if (background.y < 0)
        {
            SDL_Rect background2 = {0, Fl.getHeight() + background.y, Width, abs(background.y)};
            SDL_Rect background3 = {0, 0, Width, Height - abs(background.y)};
            Fl.render(gRenderer, 0, 0, &background2);
            BG1.render(gRenderer, 0, abs(background.y), &background3);
            SDL_Rect tam1 = {0, 0, Width, abs(background.y)};
            SDL_Rect tam2 = Plane.getPos();
            if (fn == false && CheckCollision(tam1, tam2) == true)
            {
                score += 100;
                fn = true;
            }
        }
        else
        {
            if (background.y <= Level_Height - Height)
            {
                fn = false;
                BG1.render(gRenderer, 0, 0, &background);
            }
            else
            {
                int tam = Level_Height - background.y;
                SDL_Rect background2 = {0, background.y, Width, tam};
                SDL_Rect background3 = {0, 0, Width, Fl.getHeight()};
                SDL_Rect background4 = {0, 0, Width, Height - tam - Fl.getHeight()};
                BG1.render(gRenderer, 0, 0, &background2);
                Fl.render(gRenderer, 0, tam, &background3);
                BG1.render(gRenderer, 0, tam + Fl.getHeight(), &background4);
                SDL_Rect tam1 = {0, tam, Width, Fl.getHeight()};
                SDL_Rect tam2 = Plane.getPos();
                if (fn == false && CheckCollision(tam1, tam2) == true)
                {
                    score += 100;
                    fn = true;
                }
            }
        }
        if (Plane.alive1() == true)
        {
            if (paused == false)
            {
                Plane.updateBulletRecovery(countTime);
                stringstream ss;
                ss << "Score: " << score;
                Point.loadfromrenderedtext(gRenderer, gFont, ss.str().c_str(), Color);
                ss.str("");
                countTime = pauseTime + SDL_GetTicks() - continueTime;
                realTime = countTime - startTime;
                Uint32 tg = realTime / 1000;
                Uint32 m = tg / 60;
                Uint32 s = tg - m * 60;
                Uint32 ms = (realTime - tg * 1000) * 60 / 1000;
                ss << "Time: " << m << ":" << s << ":" << ms;
                Time.loadfromrenderedtext(gRenderer, gFont, ss.str().c_str(), Color);

                // Velocity from key state every frame -> no drift when keys not held
                const Uint8 *keys = SDL_GetKeyboardState(NULL);
                Plane.setVelocityFromKeys(keys);
                int prevPlaneY = Plane.y;
                Plane.move1();
                if (Plane.y < prevPlaneY) {
                    background.y -= (prevPlaneY - Plane.y);
                    if (background.y < 0) background.y = 0;
                    if (background.y > Level_Height - Height) background.y = Level_Height - Height;
                }
                update();
                sinh(2 + realTime / 30000, 1 + realTime / 60000, realTime / 60000);
                
                // Update and handle laser collision for ability 1 (single laser)
                int i = 0;
                while (i < Lasers1.size())
                {
                    if (!Lasers1[i].isActive(countTime))
                    {
                        Lasers1.erase(Lasers1.begin() + i);
                        continue;
                    }
                    // Move laser along current plane velocity each frame so it follows the plane
                    Lasers1[i].moveBy(Plane.getVx(), Plane.getVy());
                    
                    // Check collision with enemies
                    bool hit = false;
                    for (int j = 0; j < EnemyPlane.size() && !hit; j++)
                    {
                        SDL_Rect enemyPos = {(int)EnemyPlane[j].x, (int)EnemyPlane[j].y, EnemyPlane[j].w, EnemyPlane[j].h};
                        if (Lasers1[i].checkCollision(enemyPos))
                        {
                            EnemyPlane[j].hp -= Lasers1[i].getDamage();
                            if (EnemyPlane[j].hp <= 0)
                            {
                                score += 200;
                            }
                            Lasers1.erase(Lasers1.begin() + i);
                            hit = true;
                        }
                    }
                    if (!hit)
                    {
                        for (int j = 0; j < EnemyPlane2.size() && !hit; j++)
                        {
                            SDL_Rect enemyPos = {(int)EnemyPlane2[j].x, (int)EnemyPlane2[j].y, EnemyPlane2[j].w, EnemyPlane2[j].h};
                            if (Lasers1[i].checkCollision(enemyPos))
                            {
                                EnemyPlane2[j].hp -= Lasers1[i].getDamage();
                                if (EnemyPlane2[j].hp <= 0)
                                {
                                    score += 200;
                                }
                                Lasers1.erase(Lasers1.begin() + i);
                                hit = true;
                            }
                        }
                    }
                    if (!hit) i++;
                }
                
                // Update and handle laser collision for ability 2 (triple laser)
                i = 0;
                while (i < Lasers2.size())
                {
                    if (!Lasers2[i].isActive(countTime))
                    {
                        Lasers2.erase(Lasers2.begin() + i);
                        continue;
                    }
                    // Move laser along current plane velocity each frame so it follows the plane
                    Lasers2[i].moveBy(Plane.getVx(), Plane.getVy());
                    
                    // Check collision with enemies
                    bool hit = false;
                    for (int j = 0; j < EnemyPlane.size() && !hit; j++)
                    {
                        SDL_Rect enemyPos = {(int)EnemyPlane[j].x, (int)EnemyPlane[j].y, EnemyPlane[j].w, EnemyPlane[j].h};
                        if (Lasers2[i].checkCollision(enemyPos))
                        {
                            EnemyPlane[j].hp -= Lasers2[i].getDamage();
                            if (EnemyPlane[j].hp <= 0)
                            {
                                score += 200;
                            }
                            Lasers2.erase(Lasers2.begin() + i);
                            hit = true;
                        }
                    }
                    if (!hit)
                    {
                        for (int j = 0; j < EnemyPlane2.size() && !hit; j++)
                        {
                            SDL_Rect enemyPos = {(int)EnemyPlane2[j].x, (int)EnemyPlane2[j].y, EnemyPlane2[j].w, EnemyPlane2[j].h};
                            if (Lasers2[i].checkCollision(enemyPos))
                            {
                                EnemyPlane2[j].hp -= Lasers2[i].getDamage();
                                if (EnemyPlane2[j].hp <= 0)
                                {
                                    score += 200;
                                }
                                Lasers2.erase(Lasers2.begin() + i);
                                hit = true;
                            }
                        }
                    }
                    if (!hit) i++;
                }
                
                while (i < EnemyPlane.size())
                {
                    if (EnemyPlane[i].move1(gRenderer, realTime) == false)
                    {
                        EnemyPlane[i].close();
                        EnemyPlane.erase(EnemyPlane.begin() + i);
                    }
                    else i++;
                }
                i = 0;
                while (i < EnemyPlane2.size())
                {
                    if (EnemyPlane2[i].move1(gRenderer, realTime) == false)
                    {
                        EnemyPlane2[i].close();
                        EnemyPlane2.erase(EnemyPlane2.begin() + i);
                    }
                    else i++;
                }
                i = 0;
                while (i < HPBox.size())
                {
                    if (HPBox[i].move1() == false) HPBox.erase(HPBox.begin() + i);
                    else i++;
                }
                i = 0;
                while (i < Rks.size())
                {
                    if (Rks[i].move1() == false)
                    {
                        Rks[i].close();
                        Rks.erase(Rks.begin() + i);
                    }
                    else i++;
                }
            }
            Point.render(gRenderer, 0, 0);
            Time.render(gRenderer, 0, Point.getHeight());
            
            // Display bullet info and recovery timer
            stringstream bulletSs;
            Uint32 timeSinceRecovery = countTime - Plane.recoveryTime;
            Uint32 timeUntilRecovery = (timeSinceRecovery >= 30000) ? 0 : (30000 - timeSinceRecovery) / 1000;
            
            bulletSs << "Bullets: " << Plane.bulletCount << "/" << Plane.maxBullets << " | Recovery: " << timeUntilRecovery << "s";
            
            BulletInfo.loadfromrenderedtext(gRenderer, gFont, bulletSs.str().c_str(), Color);
            BulletInfo.render(gRenderer, 0, Point.getHeight() + Time.getHeight());
            
            // Display ability cooldowns (only when on cooldown)
            Uint32 ability1CooldownRemaining = (countTime - Plane.ability1LastUse >= Plane.ability1Cooldown) ? 0 : (Plane.ability1Cooldown - (countTime - Plane.ability1LastUse)) / 1000;
            Uint32 ability2CooldownRemaining = (countTime - Plane.ability2LastUse >= Plane.ability2Cooldown) ? 0 : (Plane.ability2Cooldown - (countTime - Plane.ability2LastUse)) / 1000;
            
            if (ability1CooldownRemaining > 0 || ability2CooldownRemaining > 0)
            {
                stringstream abilitySs;
                SDL_Color abilityColor = {100, 200, 255};
                
                if (ability1CooldownRemaining > 0)
                    abilitySs << "X(Laser1):" << ability1CooldownRemaining << "s";
                
                if (ability2CooldownRemaining > 0)
                {
                    if (ability1CooldownRemaining > 0) abilitySs << " | ";
                    abilitySs << "C(Laser3):" << ability2CooldownRemaining << "s";
                }
                
                BulletInfo.loadfromrenderedtext(gRenderer, gFont, abilitySs.str().c_str(), abilityColor);
                BulletInfo.render(gRenderer, 0, Point.getHeight() + Time.getHeight() + 35);
            }
            
            // Render No Ammo popup if active (within 1 second)
            if (Plane.lastNoAmmoTime > 0 && (countTime - Plane.lastNoAmmoTime) < 1000)
            {
                SDL_Color redColor = {255, 0, 0, 255};
                NoAmmoPopup.loadfromrenderedtext(gRenderer, gFont, "No Ammo!", redColor);
                NoAmmoPopup.render(gRenderer, 30, 100);
            }
            
            Plane.render(gRenderer, gFont, MBullet);
            
            // Render lasers
            for (int i = 0; i < Lasers1.size(); i++)
                Lasers1[i].render(gRenderer);
            for (int i = 0; i < Lasers2.size(); i++)
                Lasers2[i].render(gRenderer);
            
            for (int i = 0; i < EnemyPlane.size(); i++)
                EnemyPlane[i].render(gRenderer, gFont, EPlane, Bullet);
            for (int i = 0; i < EnemyPlane2.size(); i++)
                EnemyPlane2[i].render(gRenderer, gFont, EPlane2, Bullet);
            for (int i = 0; i < HPBox.size(); i++)
                HPBox[i].render(gRenderer, hp);
            for (int i = 0; i < Rks.size(); i++)
                Rks[i].render(gRenderer, gFont, Rkt);
            if (paused == true)
            {
                PressP.render(gRenderer, (Width - PressP.getWidth()) / 2, (Height - PressP.getHeight()) / 2);
                PressB.render(gRenderer, (Width - PressB.getWidth()) / 2, (Height - PressP.getHeight()) / 2 + PressB.getHeight());
            }
            if (Plane.alive1() == false)
            {
                vector<pair<int, int> > res;
                stringstream ss;
                ss << "Your score: " << score;
                Result.loadfromrenderedtext(gRenderer, pFont, ss.str().c_str(), Color);

                ifstream f1;
                f1.open("Result.txt");
                int tam1;
                int tam2;
                while (f1 >> tam1 >> tam2)
                {
                    res.push_back({tam1, tam2});
                }
                res.push_back({score, realTime});
                sort(res.begin(), res.end(), dk);
                if (res.size() > 10) res.resize(10);

                ofstream f2;
                f2.open("Result.txt");
                for (int i = 0; i < res.size(); i++)
                {
                    f2 << res[i].first << " " << res[i].second << endl;
                }
            }
        }
        else
        {
            Die.render(gRenderer, (Width - Die.getWidth()) / 2, (Height - Die.getHeight()) / 2);
            Result.render(gRenderer, (Width - Result.getWidth()) / 2, (Height - Result.getHeight()) / 2 + Die.getHeight());
            PlayAgain.render(gRenderer, (Width / 2 - PlayAgain.getWidth()) / 2, Height - PlayAgain.getHeight());
            PressB.render(gRenderer, (Width / 2 + PressB.getWidth() / 2), Height - PressB.getHeight());
        }

        if (tam1 / 10 > timing)
        {
            Exp(gRenderer);
            timing = tam1 / (10);
        }
        SDL_RenderPresent(gRenderer);

        Uint32 tam2 = SDL_GetTicks() - tam1;
        if (tam2 < FPS) SDL_Delay(FPS - tam2);
    }
    close();
}
