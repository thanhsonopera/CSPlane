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
    int next = 0, keyrow = 0;  // Bắt đầu từ mục 0 (PLAY)
    int update_ui = 1;         // Cờ để vẽ Menu lần đầu
    vector<LTexture> menuText(5);
    
    loadMusicChoice(check_mixer, gMusic);
    Mix_PlayMusic( gMusic, -1 );
    SDL_Event e;
    loadBackground(gRenderer, Bg);
    
    // Đặt màu vẽ mặc định là ĐEN để làm viền cho hiệu ứng gập trung tâm
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    while( !quit )
    {
        // --- THAY ĐỔI 1: GIẢM KÍCH THƯỚC FONT VÀ KHOẢNG CÁCH ---
        // fsize giảm từ 50 -> 40 (chữ nhỏ hơn)
        // sum giảm từ 50 -> 45 (khoảng cách dòng hẹp hơn cho phù hợp font nhỏ)
        int h = 100, w = 100, sum = 45, fsize = 40;
        int check = 0; 
        
        // Xóa màn hình bằng màu đen ở đầu mỗi frame để tạo viền sạch
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
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
                    if (keyrow < 0) keyrow = 4; 
                    break;
                case SDLK_DOWN:
                    check = 1; 
                    keyrow++;
                    if (keyrow > 4) keyrow = 0; 
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
            if (check == 1) {
                update_ui = 1;
            }

            if (update_ui == 1) {
                loadMenuText(-1, fsize, gRenderer, menuText);

                if (keyrow >= 0 && keyrow <= 4) {
                    TTF_Font *gFontH = TTF_OpenFont("font/VGOUDYB.TTF", static_cast<int>(fsize * 1.15));
                    if (gFontH) {
                        const char *labels[5] = {"PLAY", "LEADERBOARD", "SETTING", "TUTORIAL", "EXIT"};
                        SDL_Color col = {255, 155, 0, 255}; 
                        menuText[keyrow].close(); 
                        menuText[keyrow].loadfromrenderedtext(gRenderer, gFontH, labels[keyrow], col); 
                        TTF_CloseFont(gFontH);
                    }
                }
                update_ui = 0; 
            }

            // --- THAY ĐỔI 2: HIỆU ỨNG BACKGROUND GẬP CHỤM TRUNG TÂM ---
            // 1. Mục tiêu: Bức ảnh sẽ chiếm đúng 92% chiều rộng màn hình
            float targetWidth = Width * 0.92f; 
            
            // 2. Tính tỷ lệ Scale thực tế cần dùng dựa trên ảnh gốc
            float actualScale = targetWidth / Bg.getWidth(); 

            // 3. Kích thước bức ảnh sau khi xuất ra màn hình sẽ là:
            int renderW = static_cast<int>(Bg.getWidth() * actualScale);
            int renderH = static_cast<int>(Bg.getHeight() * actualScale);

            // 4. Căn giữa tuyệt đối (Trừ đi kích thước thực tế vừa tính)
            int bgX = (Width - renderW) / 2;   
            int bgY = (Height - renderH) / 2; 

            // Vẽ background với tỷ lệ và tọa độ mới
            Bg.renderEx(gRenderer, bgX, bgY, actualScale, 255);

            // --- VẼ OVERLAY ---
            SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 60); 
            SDL_Rect full = {0, 0, Width, Height};
            SDL_RenderFillRect(gRenderer, &full);

            // --- VẼ TEXT ---
            int ty = w;
            for (int i = 0; i < 5; ++ i)
            {
                if (i == keyrow) {
                    menuText[i].renderEx(gRenderer, h + 15, ty, 1.0, 255); 
                } else {
                    menuText[i].renderEx(gRenderer, h, ty, 1.0, 200);
                }
                ty += sum;
            }
        }
        else
        {
            for (int i = 0; i < 5; i++)
                menuText[i].close();
            
            // Vẽ lại màn hình đen hoặc background khi chuẩn bị thoát
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
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
        int tg = tam2 / 1000;
        int m = tg / 60;
        int s1 = tg - m * 60;
        int ms = (tam2 - tg * 1000) * 60 / 1000;
        ss << "TOP " << dem + 1 << " : SCORE : " << tam1 << " : TIME : ";
        if (m < 10) ss << "0" << m << ":";
        else ss << m << ":";
        if (s1 < 10) ss << "0" << s1 << ":";
        else ss << s1 << ":";
        if (ms < 10) ss << "0" << ms;
        else ss << ms;
        s[dem] = ss.str();
        dem++;
    }
    while (dem < 10)
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
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    loadLeaderboardText(0, 40, gRenderer, leaderboardText, s);
    while( !quit )
    {
        int h = 0, w = 0, sum = 0, fsize = 0;
        h = 50, w = 10, sum = 40, fsize = 40;
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
            if (keyrow == 12)
            {
                quit = 1;
            }
            next = 0;
        }
            if (quit == 0)
        {
            Bg.render(gRenderer, 0, 0, &background);
            if (check) loadLeaderboardText(keyrow, fsize, gRenderer, leaderboardText, s);
            for (int i = 0; i < 12; ++ i)
            {
                if (i == 0 || i == 11)
                {
                    leaderboardText[i].render(gRenderer, h, w );
                    w += 60;
                }
                else
                {
                    leaderboardText[i].render(gRenderer, h + 100, w );
                    w += 40;
                }
            }
        }
        else
        {
            Bg.render(gRenderer, 0, 0, &background);
            for (int i = 0; i < 12; i++) leaderboardText[i].close();
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
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    loadTutorialText(0, 40, gRenderer, tutorialText);

    while( !quit )
    {
        int h = 0, w = 0, sum = 0, fsize = 0;
        h = 50, w = 10, sum = 45, fsize = 40;
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
            tutorialText[0].render(gRenderer, h, w); w += 70;
            for (int i = 1; i < 9; ++ i)
            {
                tutorialText[i].render(gRenderer, h + 100, w );
                w += sum;
            }
            tutorialText[9].render(gRenderer, h + 550, w + 50 );
            tutorialText[10].render(gRenderer, h, w + 30 );
        }
        else
        {
            for (int i = 0; i < 11; i++)
                tutorialText[i].close();
        }
        SDL_RenderPresent( gRenderer );
    }
}
void Solution(int &check_mixer, int &check_background, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic)
{
    bool quit = false;
    int next = 0, keyrow = 0, fsize = 40;
    vector<LTexture> settingText(15);
    SDL_Event e;
    loadBackground(gRenderer, Bg);

    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    loadSettingText(keyrow, fsize, gRenderer, settingText);

    while( !quit )
    {
        int h = 200, w = 150, sum = 70;
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
            for (int i = 0; i < 3; ++ i)
            {
                settingText[i].render(gRenderer, h, w );
                w += sum;
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
                settingText[i].close();
        }
        SDL_RenderPresent( gRenderer );
    }
}
void S_background(int &check_background, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont)
{
    bool quit = false;
    int next = 0, keyrow = 0, fsize = 40;
    vector<LTexture> backgroundOptionsText(5);
    SDL_Event e;
    loadBackground(gRenderer, Bg);
    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    loadBackgroundOptionsText(keyrow, fsize, gRenderer, backgroundOptionsText);

    while( !quit )
    {
        int h = 200, w = 150, sum = 70;
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
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);
            }
            if (keyrow == 2)
            {
                check_background = 2;
                Bg.loadfromfile(gRenderer, imgBg("ocean.png"));
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);
            }
            if (keyrow == 3)
            {
                check_background = 3;
                Bg.loadfromfile(gRenderer, imgBg("galaxy.png"));
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);
            }
            if (keyrow == 4) quit = 1;
            next = 0;

        }
        if (quit == 0)
        {
            if (check) loadBackgroundOptionsText(keyrow, fsize, gRenderer, backgroundOptionsText);
            Bg.render(gRenderer, 0, 0, &background);
            for (int i = 0; i < 4; ++ i)
            {
                backgroundOptionsText[i].render(gRenderer, h, w );
                w += sum;
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                backgroundOptionsText[i].close();
            }
            Bg.render(gRenderer, 0, 0, &background);
        }
        SDL_RenderPresent(gRenderer);
    }
}
void S_music(int &check_mixer, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic)
{
    bool quit = false;
    int next = 0, keyrow = 0, fsize = 40;
    vector<LTexture> musicOptionsText(5);
    SDL_Event e;
    loadBackground(gRenderer, Bg);
    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    loadMusicOptionsText(keyrow, fsize, gRenderer, musicOptionsText);

    while( !quit )
    {
        int h = 200, w = 150, sum = 70;
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
                check_mixer = 1;
                loadMusicChoice(check_mixer, gMusic);
                Mix_PlayMusic( gMusic, -1 );
            }
            if (keyrow == 2)
            {
                check_mixer = 2;
                loadMusicChoice(check_mixer, gMusic);
                Mix_PlayMusic( gMusic, -1 );
            }
            if (keyrow == 3)
            {
                check_mixer = 3;
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
            for (int i = 0; i < 4; ++ i)
            {
                musicOptionsText[i].render(gRenderer, h, w );
                w += sum;
            }
            SDL_RenderPresent(gRenderer);
        }
        else
        {
            Bg.render(gRenderer, 0, 0, &background);
            for (int i = 0; i < 4; ++ i)
            {
                musicOptionsText[i].close();
            }
            SDL_RenderPresent(gRenderer);
        }
    }
}