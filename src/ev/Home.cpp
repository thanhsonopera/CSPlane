#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "Menu.h"
#include "Paths.h"

using namespace std;



void Menu(int &check_mixer, int &check_background, SDL_Renderer *&gRenderer, vector<string> &s, LTexture Bg, SDL_Window *&gWindow, TTF_Font *gFont, TTF_Font *pFont, Mix_Music *&gMusic, vector<pair<int, int> > &res)
{
    bool quit = false;
    int next = 0, keyrow = 0; 
    int update_ui = 1;         
    vector<LTexture> menuText(MENU_MAX_ITEMS);
    
    loadMusicChoice(check_mixer, gMusic);
    Mix_PlayMusic( gMusic, -1 );
    SDL_Event e;
    loadBackground(gRenderer, Bg);
    
    SDL_SetRenderDrawColor(gRenderer, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);

    while( !quit )
    {
        int h = MENU_START_X, w = MENU_START_Y, sum = MENU_SPACING, fsize = MENU_FONT_SIZE;
        int check = 0; 
        
        SDL_SetRenderDrawColor(gRenderer, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, ALPHA_OPAQUE);
        SDL_RenderClear(gRenderer);

        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_KEYDOWN )
            {
                switch( e.key.keysym.sym )
                {
                case SDLK_UP:
                    check = 1; 
                    keyrow--;
                    if (keyrow < 0) keyrow = MENU_MAX_ITEMS - 1; 
                    break;
                case SDLK_DOWN:
                    check = 1; 
                    keyrow++;
                    if (keyrow >= MENU_MAX_ITEMS) keyrow = 0; 
                    break;
                case SDLK_e:
                    quit = 1;
                    break;
                case SDLK_RETURN:
                case SDLK_KP_ENTER:
                    next = 1;
                    break;
                }
            }
        }

        if (next == 1)
        {
            if (keyrow == 0) 
            {
                next = 0;
                xuly(check_background, gWindow, gRenderer, gFont, pFont);
                loadBackground(gRenderer, Bg);
                update_ui = 1;
            }
            else if (keyrow == 1)
            {
                next = 0;
                Leaderboard(check_mixer, gRenderer, Bg, s, gFont, gMusic);
                loadBackground(gRenderer, Bg);
                update_ui = 1;
            }
            else if (keyrow == 2)
            {
                next = 0;
                Solution(check_mixer, check_background, gRenderer, Bg, gFont, gMusic);
                loadBackground(gRenderer, Bg);
                update_ui = 1;
            }
            else if (keyrow == 3)
            {
                next = 0;
                Tutorial(check_mixer, gRenderer, Bg, gFont, gMusic);
                loadBackground(gRenderer, Bg);
                update_ui = 1;
            }
            else if (keyrow == 4) 
            {
                quit = 1;
            }
        }

        if (quit == 0)
        {
            if (check == 1) update_ui = 1;

            if (update_ui == 1) {
                loadMenuText(-1, fsize, gRenderer, menuText);

                if (keyrow >= 0 && keyrow < MENU_MAX_ITEMS) {
                    TTF_Font *gFontH = TTF_OpenFont("font/VGOUDYB.TTF", static_cast<int>(fsize * 1.15));
                    if (gFontH) {
                        const char *labels[MENU_MAX_ITEMS] = {"PLAY", "LEADERBOARD", "SETTING", "TUTORIAL", "EXIT"};
                        menuText[keyrow].close(); 
                        menuText[keyrow].loadfromrenderedtext(gRenderer, gFontH, labels[keyrow], TEXT_COLOR_HIGHLIGHT); 
                        TTF_CloseFont(gFontH);
                    }
                }
                update_ui = 0; 
            }

            float targetWidth = Width * MENU_BG_TARGET_WIDTH_RATIO; 
            float actualScale = targetWidth / Bg.getWidth(); 

            int renderW = static_cast<int>(Bg.getWidth() * actualScale);
            int renderH = static_cast<int>(Bg.getHeight() * actualScale);

            int bgX = (Width - renderW) / 2;   
            int bgY = (Height - renderH) / 2; 

            Bg.renderEx(gRenderer, bgX, bgY, actualScale, ALPHA_OPAQUE);

            SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(gRenderer, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, ALPHA_DIM); 
            SDL_Rect full = {0, 0, Width, Height};
            SDL_RenderFillRect(gRenderer, &full);

            int ty = w;
            for (int i = 0; i < MENU_MAX_ITEMS; ++i)
            {
                if (i == keyrow) {
                    menuText[i].renderEx(gRenderer, h + MENU_HIGHLIGHT_OFFSET, ty, 1.0, ALPHA_OPAQUE); 
                } else {
                    menuText[i].renderEx(gRenderer, h, ty, 1.0, TEXT_ALPHA_NORMAL);
                }
                ty += sum;
            }
        }
        else
        {
            for (int i = 0; i < MENU_MAX_ITEMS; i++)
                menuText[i].close();
            
            SDL_SetRenderDrawColor(gRenderer, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, ALPHA_OPAQUE);
            SDL_RenderClear(gRenderer);
        }
        SDL_RenderPresent( gRenderer );
    }
}

void Leaderboard(int &check_mixer, SDL_Renderer *&gRenderer, LTexture Bg, vector<string> &s, TTF_Font *gFont, Mix_Music *&gMusic)
{
    bool quit = false;
    int next = 0, keyrow = 0;

    ifstream f;
    f.open("Result.txt");
    int dem = 0;
    int tam1, tam2;
    while (f >> tam1 >> tam2)
    {
        stringstream ss;
        int tg = tam2 / MS_PER_SEC;
        int m = tg / SEC_PER_MIN;
        int s1 = tg - m * SEC_PER_MIN;
        int ms = (tam2 - tg * MS_PER_SEC) * SEC_PER_MIN / MS_PER_SEC;
        
        ss << "TOP " << dem + 1 << " : SCORE : " << tam1 << " : TIME : ";
        if (m < 10) ss << "0" << m << ":"; else ss << m << ":";
        if (s1 < 10) ss << "0" << s1 << ":"; else ss << s1 << ":";
        if (ms < 10) ss << "0" << ms; else ss << ms;
        
        s[dem] = ss.str();
        dem++;
    }
    while (dem < LB_MAX_ENTRIES)
    {
        stringstream ss;
        ss << "TOP " << dem + 1 << " : SCORE : " << 0 << " : TIME : 00:00:00";
        s[dem] = ss.str();
        dem++;
    }

    SDL_Event e;
    vector<LTexture> leaderboardText(15);
    loadBackground(gRenderer, Bg);

    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);

    loadLeaderboardText(0, LB_FONT_SIZE, gRenderer, leaderboardText, s);
    
    while( !quit )
    {
        int h = LB_START_X, w = LB_START_Y, sum = LB_ITEM_SPACING, fsize = LB_FONT_SIZE;
        int check = 0;
        
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
                switch( e.key.keysym.sym )
                {
                case SDLK_UP:
                    check = 1, keyrow = navigateLeaderboard(keyrow, -1);
                    break;
                case SDLK_DOWN:
                    check = 1, keyrow = navigateLeaderboard(keyrow, 1);
                    break;
                case SDLK_e:
                    exit(0);
                    break;
                case SDLK_b:
                    quit = 1;
                    break;
                case SDLK_RETURN:
                    next = 1;
                    break;
                }

        if (next == 1)
        {
            if (keyrow == LB_TOTAL_TEXT_ITEMS) quit = 1;
            next = 0;
        }
        
        if (quit == 0)
        {
            Bg.render(gRenderer, 0, 0, &background);
            if (check) loadLeaderboardText(keyrow, fsize, gRenderer, leaderboardText, s);
            
            for (int i = 0; i < LB_TOTAL_TEXT_ITEMS; ++i)
            {
                if (i == 0 || i == LB_TOTAL_TEXT_ITEMS - 1)
                {
                    leaderboardText[i].render(gRenderer, h, w );
                    w += LB_HEADER_SPACING;
                }
                else
                {
                    leaderboardText[i].render(gRenderer, h + LB_INDENT_X, w );
                    w += LB_ITEM_SPACING;
                }
            }
        }
        else
        {
            Bg.render(gRenderer, 0, 0, &background);
            for (int i = 0; i < LB_TOTAL_TEXT_ITEMS; i++) leaderboardText[i].close();
        }
        SDL_RenderPresent( gRenderer );
    }
}

void Tutorial(int &check_mixer, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic)
{
    bool quit = false;
    int next = 0, keyrow = 0;
    SDL_Event e;
    vector<LTexture> tutorialText(15);
    loadBackground(gRenderer, Bg);
    
    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);
    loadTutorialText(0, TUT_FONT_SIZE, gRenderer, tutorialText);

    while( !quit )
    {
        int h = TUT_START_X, w = TUT_START_Y, sum = TUT_SPACING, fsize = TUT_FONT_SIZE;
        int check = 0;
        
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
                switch( e.key.keysym.sym )
                {
                case SDLK_UP:
                    check = 1, keyrow = navigateTutorialMenu(keyrow, -1);
                    break;
                case SDLK_DOWN:
                    check = 1, keyrow = navigateTutorialMenu(keyrow, 1);
                    break;
                case SDLK_e:
                    exit(0);
                    break;
                case SDLK_b:
                    quit = 1;
                    break;
                case SDLK_RETURN:
                    next = 1;
                    break;
                }
                
        if (next == 1)
        {
            if (keyrow == 2) quit = 1;
            next = 0;
        }
        
        Bg.render(gRenderer, 0, 0, &background);

        if (quit == 0)
        {
            if (check) loadTutorialText(keyrow, fsize, gRenderer, tutorialText);
            
            tutorialText[0].render(gRenderer, h, w); 
            w += TUT_HEADER_SPACING;
            
            for (int i = 1; i < 9; ++i)
            {
                tutorialText[i].render(gRenderer, h + TUT_INDENT_X, w );
                w += sum;
            }
            tutorialText[9].render(gRenderer, h + 550, w + 50 ); // Có thể đẩy nốt tọa độ này lên Constants nếu cần
            tutorialText[10].render(gRenderer, h, w + 30 );
        }
        else
        {
            for (int i = 0; i < 11; i++) tutorialText[i].close();
        }
        SDL_RenderPresent( gRenderer );
    }
}

void Solution(int &check_mixer, int &check_background, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic)
{
    bool quit = false;
    int next = 0, keyrow = 0, fsize = SET_FONT_SIZE;
    vector<LTexture> settingText(15);
    SDL_Event e;
    loadBackground(gRenderer, Bg);

    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);
    loadSettingText(keyrow, fsize, gRenderer, settingText);

    while( !quit )
    {
        int h = SET_START_X, w = SET_START_Y, sum = SET_SPACING;
        int check = 0;
        
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
                switch( e.key.keysym.sym )
                {
                case SDLK_UP:
                    check = 1, keyrow = navigateSettingsMenu(keyrow, -1);
                    break;
                case SDLK_DOWN:
                    check = 1, keyrow = navigateSettingsMenu(keyrow, 1);
                    break;
                case SDLK_b:
                    quit = 1;
                    break;
                case SDLK_e:
                    exit(0);
                    break;
                case SDLK_RETURN:
                    next = 1;
                    break;
                }
                
        if (next)
        {
            if (keyrow == 1)
            {
                S_background(check_background, gRenderer, Bg, gFont);
                loadBackground(gRenderer, Bg);
                SDL_RenderClear(gRenderer);
                check = 1;
            }
            if (keyrow == 2)
            {
                S_music(check_mixer, gRenderer, Bg, gFont, gMusic);
                loadBackground(gRenderer, Bg);
                SDL_RenderClear(gRenderer);
                check = 1;
            }
            if (keyrow == 3) quit = 1;
            next = 0;
        }

        Bg.render(gRenderer, 0, 0, &background);

        if (quit == 0)
        {
            if (check) loadSettingText(keyrow, fsize, gRenderer, settingText);
            for (int i = 0; i < SET_MAIN_ITEMS; ++i)
            {
                settingText[i].render(gRenderer, h, w );
                w += sum;
            }
        }
        else
        {
            for (int i = 0; i < SET_MAIN_ITEMS; i++) settingText[i].close();
        }
        SDL_RenderPresent( gRenderer );
    }
}

void S_background(int &check_background, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont)
{
    bool quit = false;
    int next = 0, keyrow = 0, fsize = SET_FONT_SIZE;
    vector<LTexture> backgroundOptionsText(5);
    SDL_Event e;
    loadBackground(gRenderer, Bg);
    
    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);
    loadBackgroundOptionsText(keyrow, fsize, gRenderer, backgroundOptionsText);

    while( !quit )
    {
        int h = SET_START_X, w = SET_START_Y, sum = SET_SPACING;
        int check = 0;
        
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
                switch( e.key.keysym.sym )
                {
                case SDLK_UP:
                    check = 1, keyrow = navigateOptionsList(keyrow, -1);
                    break;
                case SDLK_DOWN:
                    check = 1, keyrow = navigateOptionsList(keyrow, 1);
                    break;
                case SDLK_b:
                    quit = 1;
                    break;
                case SDLK_e:
                    exit(0);
                    break;
                case SDLK_RETURN:
                    next = 1;
                    break;
                }
                
        if (next)
        {
            if (keyrow == 1)
            {
                check_background = 1;
                Bg.loadfromfile(gRenderer, imgBg("Jungle.png"));
                SDL_SetRenderDrawColor(gRenderer, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, ALPHA_OPAQUE);
                SDL_RenderClear(gRenderer);
            }
            if (keyrow == 2)
            {
                check_background = 2;
                Bg.loadfromfile(gRenderer, imgBg("ocean.png"));
                SDL_SetRenderDrawColor(gRenderer, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, ALPHA_OPAQUE);
                SDL_RenderClear(gRenderer);
            }
            if (keyrow == 3)
            {
                check_background = 3;
                Bg.loadfromfile(gRenderer, imgBg("galaxy.png"));
                SDL_SetRenderDrawColor(gRenderer, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, ALPHA_OPAQUE);
                SDL_RenderClear(gRenderer);
            }
            if (keyrow == 4) quit = 1;
            next = 0;
        }
        
        if (quit == 0)
        {
            if (check) loadBackgroundOptionsText(keyrow, fsize, gRenderer, backgroundOptionsText);
            Bg.render(gRenderer, 0, 0, &background);
            for (int i = 0; i < SET_SUB_ITEMS; ++i)
            {
                backgroundOptionsText[i].render(gRenderer, h, w );
                w += sum;
            }
        }
        else
        {
            for (int i = 0; i < SET_SUB_ITEMS; i++) backgroundOptionsText[i].close();
            Bg.render(gRenderer, 0, 0, &background);
        }
        SDL_RenderPresent(gRenderer);
    }
}

void S_music(int &check_mixer, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic)
{
    bool quit = false;
    int next = 0, keyrow = 0, fsize = SET_FONT_SIZE;
    vector<LTexture> musicOptionsText(5);
    SDL_Event e;
    loadBackground(gRenderer, Bg);
    
    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);
    loadMusicOptionsText(keyrow, fsize, gRenderer, musicOptionsText);

    while( !quit )
    {
        int h = SET_START_X, w = SET_START_Y, sum = SET_SPACING;
        int check = 0;
        
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
                switch( e.key.keysym.sym )
                {
                case SDLK_UP:
                    check = 1, keyrow = navigateOptionsList(keyrow, -1);
                    break;
                case SDLK_DOWN:
                    check = 1, keyrow = navigateOptionsList(keyrow, 1);
                    break;
                case SDLK_b:
                    quit = 1;
                    break;
                case SDLK_e:
                    exit(0);
                    break;
                case SDLK_RETURN:
                    next = 1;
                    break;
                }
                
        if (next)
        {
            if (keyrow == 1 || keyrow == 2 || keyrow == 3) 
            {
                check_mixer = keyrow;
                loadMusicChoice(check_mixer, gMusic);
                Mix_PlayMusic( gMusic, -1 );
            }
            if (keyrow == 4) quit = 1;
            next = 0;
        }
        
        if (quit == 0)
        {
            Bg.render(gRenderer, 0, 0, &background);
            if (check) loadMusicOptionsText(keyrow, fsize, gRenderer, musicOptionsText);
            for (int i = 0; i < SET_SUB_ITEMS; ++i)
            {
                musicOptionsText[i].render(gRenderer, h, w );
                w += sum;
            }
            SDL_RenderPresent(gRenderer);
        }
        else
        {
            Bg.render(gRenderer, 0, 0, &background);
            for (int i = 0; i < SET_SUB_ITEMS; ++i) musicOptionsText[i].close();
            SDL_RenderPresent(gRenderer);
        }
    }
}