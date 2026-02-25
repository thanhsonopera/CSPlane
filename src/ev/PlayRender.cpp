#include <fstream>
#include <sstream>
#include <algorithm>
#include "Play.h"
#include "Paths.h"

void loadmedia(SDL_Renderer *&gRenderer, TTF_Font *&gFont, TTF_Font *&pFont)
{
    gFont = TTF_OpenFont("font/VAPTIMN.TTF", FONT_SIZE_SMALL);
    if (!gFont) gFont = TTF_OpenFont("VAPTIMN.TTF", FONT_SIZE_SMALL);
    pFont = TTF_OpenFont("font/VAVOBI.TTF", FONT_SIZE_LARGE);
    if (!pFont) pFont = TTF_OpenFont("VAVOBI.TTF", FONT_SIZE_LARGE);
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

void loadbg(int &check_background, SDL_Renderer *&gRenderer)
{
    if (check_background == 1) BG1.loadfromfile(gRenderer, imgBg("Jungle.png"));
    if (check_background == 2) BG1.loadfromfile(gRenderer, imgBg("ocean.png"));
    if (check_background == 3) BG1.loadfromfile(gRenderer, imgBg("galaxy.png"));
}

void renderBackgroundAndFinishLine(bool &fn, SDL_Renderer *&gRenderer) {
    if (background.y < 0) {
        SDL_Rect background2 = {0, Fl.getHeight() + background.y, Width, abs(background.y)};
        SDL_Rect background3 = {0, 0, Width, Height - abs(background.y)};
        Fl.render(gRenderer, 0, 0, &background2);
        BG1.render(gRenderer, 0, abs(background.y), &background3);
        SDL_Rect tam1 = {0, 0, Width, abs(background.y)};
        SDL_Rect tam2 = Plane.getPos();
        if (fn == false && CheckCollision(tam1, tam2) == true) {
            score += SCORE_FINISH_LINE;
            fn = true;
        }
    } else {
        if (background.y <= Level_Height - Height) {
            fn = false;
            BG1.render(gRenderer, 0, 0, &background);
        } else {
            int tam = Level_Height - background.y;
            SDL_Rect background2 = {0, background.y, Width, tam};
            SDL_Rect background3 = {0, 0, Width, Fl.getHeight()};
            SDL_Rect background4 = {0, 0, Width, Height - tam - Fl.getHeight()};
            BG1.render(gRenderer, 0, 0, &background2);
            Fl.render(gRenderer, 0, tam, &background3);
            BG1.render(gRenderer, 0, tam + Fl.getHeight(), &background4);
            SDL_Rect tam1 = {0, tam, Width, Fl.getHeight()};
            SDL_Rect tam2 = Plane.getPos();
            if (fn == false && CheckCollision(tam1, tam2) == true) {
                score += SCORE_FINISH_LINE;
                fn = true;
            }
        }
    }
}

void updateHUD(SDL_Renderer *&gRenderer, TTF_Font *&gFont) {
    std::stringstream ss;
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
}

void renderGame(SDL_Renderer *&gRenderer, TTF_Font *&gFont, TTF_Font *&pFont) {
    Point.render(gRenderer, 0, 0);
    Time.render(gRenderer, 0, Point.getHeight());

    std::stringstream bulletSs;
    Uint32 timeSinceRecovery = countTime - Plane.recoveryTime;
    Uint32 timeUntilRecovery = (timeSinceRecovery >= PLANE_RECOVERY_MS) ? 0 : (PLANE_RECOVERY_MS - timeSinceRecovery) / 1000;
    bulletSs << "Bullets: " << Plane.bulletCount << "/" << Plane.maxBullets << " | Recovery: " << timeUntilRecovery << "s";
    BulletInfo.loadfromrenderedtext(gRenderer, gFont, bulletSs.str().c_str(), Color);
    BulletInfo.render(gRenderer, 0, Point.getHeight() + Time.getHeight());

    Uint32 ability1CooldownRemaining = (countTime - Plane.ability1LastUse >= Plane.ability1Cooldown) ? 0 : (Plane.ability1Cooldown - (countTime - Plane.ability1LastUse)) / 1000;
    Uint32 ability2CooldownRemaining = (countTime - Plane.ability2LastUse >= Plane.ability2Cooldown) ? 0 : (Plane.ability2Cooldown - (countTime - Plane.ability2LastUse)) / 1000;
    if (ability1CooldownRemaining > 0 || ability2CooldownRemaining > 0) {
        std::stringstream abilitySs;
        SDL_Color abilityColor = {COLOR_ABILITY_R, COLOR_ABILITY_G, COLOR_ABILITY_B};
        if (ability1CooldownRemaining > 0)
            abilitySs << "X(Laser1):" << ability1CooldownRemaining << "s";
        if (ability2CooldownRemaining > 0) {
            if (ability1CooldownRemaining > 0) abilitySs << " | ";
            abilitySs << "C(Laser3):" << ability2CooldownRemaining << "s";
        }
        BulletInfo.loadfromrenderedtext(gRenderer, gFont, abilitySs.str().c_str(), abilityColor);
        BulletInfo.render(gRenderer, 0, Point.getHeight() + Time.getHeight() + ABILITY_UI_OFFSET_Y);
    }

    if (Plane.lastNoAmmoTime > 0 && (countTime - Plane.lastNoAmmoTime) < NO_AMMO_POPUP_MS) {
        SDL_Color redColor = {255, 0, 0, 255};
        NoAmmoPopup.loadfromrenderedtext(gRenderer, gFont, "No Ammo!", redColor);
        NoAmmoPopup.render(gRenderer, NO_AMMO_POPUP_X, NO_AMMO_POPUP_Y);
    }

    Plane.render(gRenderer, gFont, MBullet);
    for (int i = 0; i < (int)Lasers1.size(); i++) Lasers1[i].render(gRenderer);
    for (int i = 0; i < (int)Lasers2.size(); i++) Lasers2[i].render(gRenderer);
    for (int i = 0; i < (int)EnemyPlane.size(); i++) EnemyPlane[i].render(gRenderer, gFont, EPlane, Bullet);
    for (int i = 0; i < (int)EnemyPlane2.size(); i++) EnemyPlane2[i].render(gRenderer, gFont, EPlane2, Bullet);
    for (int i = 0; i < (int)HPBox.size(); i++) HPBox[i].render(gRenderer, hp);
    for (int i = 0; i < (int)Rks.size(); i++) Rks[i].render(gRenderer, gFont, Rkt);
    if (paused == true) {
        PressP.render(gRenderer, (Width - PressP.getWidth()) / 2, (Height - PressP.getHeight()) / 2);
        PressB.render(gRenderer, (Width - PressB.getWidth()) / 2, (Height - PressP.getHeight()) / 2 + PressB.getHeight());
    }

    if (Plane.alive1() == false) {
        std::vector<std::pair<int, int> > res;
        std::stringstream ss;
        ss << "Your score: " << score;
        Result.loadfromrenderedtext(gRenderer, pFont, ss.str().c_str(), Color);
        std::ifstream f1("Result.txt");
        int a, b;
        while (f1 >> a >> b) res.push_back({a, b});
        res.push_back({score, realTime});
        std::sort(res.begin(), res.end(), dk);
        if (res.size() > TOP_SCORES_COUNT) res.resize(TOP_SCORES_COUNT);
        std::ofstream f2("Result.txt");
        for (int i = 0; i < (int)res.size(); i++) f2 << res[i].first << " " << res[i].second << std::endl;
    }
}

void renderDeathScreen(SDL_Renderer *&gRenderer, TTF_Font *&pFont) {
    Die.render(gRenderer, (Width - Die.getWidth()) / 2, (Height - Die.getHeight()) / 2);
    Result.render(gRenderer, (Width - Result.getWidth()) / 2, (Height - Result.getHeight()) / 2 + Die.getHeight());
    PlayAgain.render(gRenderer, (Width / 2 - PlayAgain.getWidth()) / 2, Height - PlayAgain.getHeight());
    PressB.render(gRenderer, (Width / 2 + PressB.getWidth() / 2), Height - PressB.getHeight());
}
