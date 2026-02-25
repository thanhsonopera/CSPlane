#include <algorithm>
#include <sstream>
#include "Play.h"

// Random EnemyPlane
void sinh(int sl1, int sl2, int sl3)
{
    int x1 = min1 + rand() % (max1 - min1);
    if (x1 == 5 && EnemyPlane.size() < std::min(sl1, 5))
    {
        int y = 0;
        while (true)
        {
            y = 0 + rand() % (Width - Plane_w);
            bool ok = true;
            for (int i = 0; i < (int)EnemyPlane.size(); i++)
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
            for (int i = 0; i < (int)EnemyPlane2.size(); i++)
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
    if (x2 == 10 && EnemyPlane2.size() < std::min(sl2, 3))
    {
        int y = 0;
        while (true)
        {
            y = 0 + rand() % (Width - Plane2_w);
            bool ok = true;
            for (int i = 0; i < (int)EnemyPlane.size(); i++)
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
            for (int i = 0; i < (int)EnemyPlane2.size(); i++)
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

    int x3 = min1 + rand() % (max1 + SPAWN_RAND_EXTRA - min1);
    if (x3 == 15 && Rks.size() < std::min(sl3, 3))
    {
        SDL_Rect vt = Plane.getPos();
        Rocket tam(vt.x + (vt.w - Rocket_w) / 2, -Rocket_h, realTime);
        Rks.push_back(tam);
    }
}

// Update Objects
void update()
{
    // Ally plane collide enemy planes
    std::vector <SDL_Rect> tam1 = Plane.getRect();
    for (int i = 0; i < (int)EnemyPlane.size(); i++)
        if (EnemyPlane[i].alive1() == true)
        {
            std::vector <SDL_Rect> tam2 = EnemyPlane[i].getRect();
            for (int j = 0; j < (int)tam1.size(); j++)
            {
                bool ok = true;
                for (int k = 0; k < (int)tam2.size(); k++)
                    if (CheckCollision(tam1[j], tam2[k]) == true)
                    {
                        Plane.hp -= DAMAGE_PLANE_HIT_ENEMY1;
                        EnemyPlane[i].hp = 0;
                        ok = false;
                        break;
                    }
                if (ok == false) break;
            }
        }

    for (int i = 0; i < (int)EnemyPlane2.size(); i++)
        if (EnemyPlane2[i].alive1() == true)
        {
            std::vector <SDL_Rect> tam2 = EnemyPlane2[i].getRect();
            for (int j = 0; j < (int)tam1.size(); j++)
            {
                bool ok = true;
                for (int k = 0; k < (int)tam2.size(); k++)
                    if (CheckCollision(tam1[j], tam2[k]) == true)
                    {
                        Plane.hp -= DAMAGE_PLANE_HIT_ENEMY2;
                        EnemyPlane2[i].hp = 0;
                        ok = false;
                        break;
                    }
                if (ok == false) break;
            }
        }

    // Enemy planes collide each other and with Enemy2

    for (int i = 0; i < (int)EnemyPlane.size(); i++)
        if (EnemyPlane[i].alive1() == true)
        {
            SDL_Rect tam2 = {EnemyPlane[i].x, EnemyPlane[i].y, EnemyPlane[i].w, EnemyPlane[i].h};
            for (int j = i + 1; j < (int)EnemyPlane.size(); j++)
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

    for (int i = 0; i < (int)EnemyPlane2.size(); i++)
        if (EnemyPlane2[i].alive1() == true)
        {
            SDL_Rect tam2 = {EnemyPlane2[i].x, EnemyPlane2[i].y - EnemyPlane2[i].status.getHeight(), EnemyPlane2[i].w, EnemyPlane2[i].h + EnemyPlane2[i].status.getHeight()};
            for (int j = i + 1; j < (int)EnemyPlane2.size(); j++)
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

    for (int i = 0; i < (int)EnemyPlane.size(); i++)
        if (EnemyPlane[i].alive1() == true)
        {
            SDL_Rect tam2 = {EnemyPlane[i].x, EnemyPlane[i].y, EnemyPlane[i].w, EnemyPlane[i].h};
            for (int j = 0; j < (int)EnemyPlane2.size(); j++)
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

    // Bullets vs enemies

    int i = 0;

    while (i < (int)Plane.bullet.size())
    {
        SDL_Rect tam2 = Plane.bullet[i].getRect();
        bool ok = true;
        for (int j = 0; j < (int)EnemyPlane.size(); j++)
            if (EnemyPlane[j].alive1() == true)
            {
                std::vector <SDL_Rect> tam3 = EnemyPlane[j].getRect();
                for (int k = 0; k < (int)tam3.size(); k++)
                    if (CheckCollision(tam2, tam3[k]) == true)
                    {
                        EnemyPlane[j].hp -= DAMAGE_BULLET_HIT_ENEMY;
                        Plane.bullet.erase(Plane.bullet.begin() + i);
                        ok = false;
                        break;
                    }
                if (ok == false) break;
            }
        if (ok == true)
        {
            for (int j = 0; j < (int)EnemyPlane2.size(); j++)
                if (EnemyPlane2[j].alive1() == true)
                {
                    std::vector <SDL_Rect> tam3 = EnemyPlane2[j].getRect();
                    for (int k = 0; k < (int)tam3.size(); k++)
                        if (CheckCollision(tam2, tam3[k]) == true)
                        {
                            EnemyPlane2[j].hp -= DAMAGE_BULLET_HIT_ENEMY;
                            Plane.bullet.erase(Plane.bullet.begin() + i);
                            ok = false;
                            break;
                        }
                    if (ok == false) break;
                }
        }
        if (ok == true) i++;
    }

    // Bullets vs rockets

    i = 0;
    while (i < (int)Plane.bullet.size())
    {
        SDL_Rect tam2 = Plane.bullet[i].getRect();
        bool ok = true;
        for (int j = 0; j < (int)Rks.size(); j++)
        {
            SDL_Rect tam3 = Rks[j].getPos();
            if (CheckCollision(tam2, tam3) == true)
            {
                Rks[j].hp -= DAMAGE_BULLET_HIT_ROCKET;
                Plane.bullet.erase(Plane.bullet.begin() + i);
                ok = false;
            }
            if (ok == false) break;
        }
        if (ok == true) i++;
    }


    // Enemy bullets vs ally plane

    for (int j = 0; j < (int)EnemyPlane.size(); j++)
    {
        int k = 0;
        while (k < (int)EnemyPlane[j].bullet.size())
        {
            bool ok = true;
            SDL_Rect tam2 = EnemyPlane[j].bullet[k].getRect();
            for (int e = 0; e < (int)tam1.size(); e++)
                if (CheckCollision(tam2, tam1[e]) == true)
                {
                    Plane.hp -= DAMAGE_ENEMY_BULLET;
                    EnemyPlane[j].bullet.erase(EnemyPlane[j].bullet.begin() + k);
                    ok = false;
                    break;
                }
            if (ok == true) k++;
        }
    }

    for (int j = 0; j < (int)EnemyPlane2.size(); j++)
    {
        int k = 0;
        while (k < (int)EnemyPlane2[j].bullet.size())
        {
            bool ok = true;
            SDL_Rect tam2 = EnemyPlane2[j].bullet[k].getRect();
            for (int e = 0; e < (int)tam1.size(); e++)
                if (CheckCollision(tam2, tam1[e]) == true)
                {
                    Plane.hp -= DAMAGE_ENEMY_BULLET;
                    EnemyPlane2[j].bullet.erase(EnemyPlane2[j].bullet.begin() + k);
                    ok = false;
                    break;
                }
            if (ok == true) k++;
        }
    }

    // Rockets vs ally plane
    for (int j = 0; j < (int)Rks.size(); j++)
    {
        std::vector <SDL_Rect> tam2 = Plane.getRect();
        SDL_Rect tam3 = Rks[j].getPos();
        for (int e = 0; e < (int)tam2.size(); e++)
            if (CheckCollision(tam3, tam2[e]) == true)
            {
                Plane.hp -= DAMAGE_ROCKET_HIT_PLANE;
                Rks[j].hp = 0;
                break;
            }
    }

    // HP boxes
    i = 0;
    while (i < (int)HPBox.size())
    {
        bool ok = true;
        SDL_Rect tam2 = {HPBox[i].x, HPBox[i].y, HPBox[i].w, HPBox[i].h};
        SDL_Rect tam3 = {Plane.x, Plane.y, Plane.w, Plane.h};
        if (CheckCollision(tam2, tam3) == true)
        {
            Plane.hp += HP_BOX_HEAL;
            HPBox.erase(HPBox.begin() + i);
            ok = false;
        }
        if (ok == true) i++;
    }

    // Explosions spawn
    if (Plane.alive1() == true)
    {
        if (Plane.hp <= 0)
        {
            Plane.alive = false;
            BigBang k(Plane.x, Plane.y);
            Explosions.push_back(k);
        }
    }

    for (int j = 0; j < (int)EnemyPlane.size(); j++)
        if (EnemyPlane[j].alive1() == true)
        {
            if (EnemyPlane[j].hp <= 0)
            {
                EnemyPlane[j].alive = false;
                score += SCORE_ENEMY1;
                BigBang k(EnemyPlane[j].x, EnemyPlane[j].y);
                Explosions.push_back(k);
                int t1 = rand() % HP_DROP_RAND_MOD;
                if (t1 == HP_DROP_RAND_VAL)
                {
                    HP t2(EnemyPlane[j].x, EnemyPlane[j].y);
                    HPBox.push_back(t2);
                }
            }
        }
    for (int j = 0; j < (int)EnemyPlane2.size(); j++)
        if (EnemyPlane2[j].alive1() == true)
        {
            if (EnemyPlane2[j].hp <= 0)
            {
                EnemyPlane2[j].alive = false;
                score += SCORE_ENEMY2;
                BigBang k(EnemyPlane2[j].x, EnemyPlane2[j].y);
                Explosions.push_back(k);
                int t1 = rand() % HP_DROP_RAND_MOD;
                if (t1 == HP_DROP_RAND_VAL)
                {
                    HP t2(EnemyPlane2[j].x, EnemyPlane2[j].y);
                    HPBox.push_back(t2);
                }
            }
        }
    for (int j = 0; j < (int)Rks.size(); j++)
        if (Rks[j].hp <= 0)
    {
        BigBang k(Rks[j].x, Rks[j].y);
        Explosions.push_back(k);
    }
}

// Explosions
void Exp(SDL_Renderer *&gRenderer)
{
    int i = 0;
    while (i < (int)Explosions.size())
    {
        if (Explosions[i].render(gRenderer, BB) == false) Explosions.erase(Explosions.begin() + i);
        else i++;
    }
}

static void updateLasers(std::vector<Laser> &lasers) {
    int i = 0;
    while (i < (int)lasers.size()) {
        if (!lasers[i].isActive(countTime)) {
            lasers.erase(lasers.begin() + i);
            continue;
        }
        lasers[i].moveBy(Plane.getVx(), Plane.getVy());
        bool hit = false;
        for (int j = 0; j < (int)EnemyPlane.size() && !hit; j++) {
            SDL_Rect enemyPos = {(int)EnemyPlane[j].x, (int)EnemyPlane[j].y, EnemyPlane[j].w, EnemyPlane[j].h};
            if (lasers[i].checkCollision(enemyPos)) {
                EnemyPlane[j].hp -= lasers[i].getDamage();
                if (EnemyPlane[j].hp <= 0) score += SCORE_LASER_KILL;
                lasers.erase(lasers.begin() + i);
                hit = true;
            }
        }
        if (!hit) {
            for (int j = 0; j < (int)EnemyPlane2.size() && !hit; j++) {
                SDL_Rect enemyPos = {(int)EnemyPlane2[j].x, (int)EnemyPlane2[j].y, EnemyPlane2[j].w, EnemyPlane2[j].h};
                if (lasers[i].checkCollision(enemyPos)) {
                    EnemyPlane2[j].hp -= lasers[i].getDamage();
                    if (EnemyPlane2[j].hp <= 0) score += SCORE_LASER_KILL;
                    lasers.erase(lasers.begin() + i);
                    hit = true;
                }
            }
        }
        if (!hit) i++;
    }
}

void updateLasersAndCollisions() {
    updateLasers(Lasers1);
    updateLasers(Lasers2);
}

void updateWorld(SDL_Renderer *&gRenderer) {
    Plane.updateBulletRecovery(countTime);
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
    sinh(2 + realTime / SINH_TIME_DIV_30K, 1 + realTime / SINH_TIME_DIV_60K, realTime / SINH_TIME_DIV_60K);

    int i = 0;
    while (i < (int)EnemyPlane.size()) {
        if (EnemyPlane[i].move1(gRenderer, realTime) == false) {
            EnemyPlane[i].close();
            EnemyPlane.erase(EnemyPlane.begin() + i);
        } else i++;
    }
    i = 0;
    while (i < (int)EnemyPlane2.size()) {
        if (EnemyPlane2[i].move1(gRenderer, realTime) == false) {
            EnemyPlane2[i].close();
            EnemyPlane2.erase(EnemyPlane2.begin() + i);
        } else i++;
    }
    i = 0;
    while (i < (int)HPBox.size()) {
        if (HPBox[i].move1() == false) HPBox.erase(HPBox.begin() + i);
        else i++;
    }
    i = 0;
    while (i < (int)Rks.size()) {
        if (Rks[i].move1() == false) {
            Rks[i].close();
            Rks.erase(Rks.begin() + i);
        } else i++;
    }
}
