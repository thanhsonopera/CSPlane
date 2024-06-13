#include <iostream>
#include <fstream>

#include "Menu.h"

void Menu(int &check_mixer, int &check_background, SDL_Renderer *&gRenderer, string *&s, LTexture Bg, SDL_Window *&gWindow, TTF_Font *gFont, TTF_Font *pFont, Mix_Music *&gMusic, vector<pair<int, int> > &res)
{
    bool quit = false;
    int next = 0, keyrow = 0;
    LTexture *gTextTexture = new LTexture[5];
    loadMedia_5(check_mixer, gMusic);
    Mix_PlayMusic( gMusic, -1 );
    SDL_Event e;
    loadMedia_1(gRenderer, Bg);
    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    loadMedia_2(0, 50, gRenderer, gTextTexture);
    while( !quit )
    {
        int h = 0, w = 0, sum = 0, fsize = 0;
        h = 100, w = 100, sum = 50, fsize = 50;
        int check = 0;
        SDL_Rect background = {0, 0, Width, Height};
        Bg.render(gRenderer, 0, 0, &background);
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
                switch( e.key.keysym.sym )
                {
                case SDLK_UP:
                    check = 1, keyrow = Update(keyrow, -1);
                    break;
                case SDLK_DOWN:
                    check = 1, keyrow = Update(keyrow, 1);
                    break;
                case SDLK_e:
                    quit = 1;
                    break;
                case SDLK_b:
                    keyrow = 0;
                    break;
                case SDLK_RETURN:
                    next = 1;
                    break;
                }
        if (next == 1)
        {
            if (keyrow == 0) next = 0;
            else if (keyrow == 1)
            {
                next = 0;
                xuly(check_background, gWindow, gRenderer, gFont, pFont);
                loadMedia_1(gRenderer, Bg);
                SDL_RenderClear(gRenderer);
                check = 1;
            }
            else if (keyrow == 2)
            {
                next = 0;
                Leaderboard(check_mixer, gRenderer, Bg, s, gFont, gMusic);
                loadMedia_1(gRenderer, Bg);
                SDL_RenderClear(gRenderer);
                check = 1;
            }
            else if (keyrow == 3)
            {
                next = 0;
                Solution(check_mixer, check_background, gRenderer, Bg, gFont, gMusic);
                loadMedia_1(gRenderer, Bg);
                SDL_RenderClear(gRenderer);
                check = 1;
            }
            else if (keyrow == 4)
            {
                Tutorial(check_mixer, gRenderer, Bg, gFont, gMusic);
                loadMedia_1(gRenderer, Bg);
                SDL_RenderClear(gRenderer);
                check = 1;
                next = 0;
            }
            else if (keyrow == 5)
            {
                quit = 1;
            }
        }


        if (quit == 0)
        {
            Bg.render(gRenderer, 0, 0, &background);
            if (check) loadMedia_2(keyrow, fsize, gRenderer, gTextTexture);

            for (int i = 0; i < 5; ++ i)
            {
                gTextTexture[i].render(gRenderer, h, w );
                w += sum;
            }
        }
        else
        {
            for (int i = 0; i < 5; i++)
                gTextTexture[i].close();
            Bg.render(gRenderer, 0, 0, &background);
        }
        SDL_RenderPresent( gRenderer );

    }
}

void Leaderboard(int &check_mixer, SDL_Renderer *&gRenderer, LTexture Bg, string *&s, TTF_Font *gFont, Mix_Music *&gMusic)
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
    LTexture *gTextTexture_2 = new LTexture[15];
    loadMedia_1(gRenderer, Bg);

    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    loadMedia_3(0, 40, gRenderer, gTextTexture_2, s);
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
                    check = 1, keyrow = Update_2(keyrow, -1);
                    break;
                case SDLK_DOWN:
                    check = 1, keyrow = Update_2(keyrow, 1);
                    break;
                case SDLK_e:
                    exit(0);
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
            if (check) loadMedia_3(keyrow, fsize, gRenderer, gTextTexture_2, s);
            for (int i = 0; i < 12; ++ i)
            {
                if (i == 0 || i == 11)
                {
                    gTextTexture_2[i].render(gRenderer, h, w );
                    w += 60;
                }
                else
                {
                    gTextTexture_2[i].render(gRenderer, h + 100, w );
                    w += 40;
                }
            }
        }
        else
        {
            Bg.render(gRenderer, 0, 0, &background);
            for (int i = 0; i < 12; i++) gTextTexture_2[i].close();
        }
        SDL_RenderPresent( gRenderer );
    }

}
void Tutorial(int &check_mixer, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic)
{
    bool quit = false;
    int next = 0, keyrow = 0;
    SDL_Event e;
    LTexture *gTextTexture_3 = new LTexture[15];
    loadMedia_1(gRenderer, Bg);

    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    loadMedia_4(0, 40, gRenderer, gTextTexture_3);

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
                    check = 1, keyrow = Update_4(keyrow, -1);
                    break;
                case SDLK_DOWN:
                    check = 1, keyrow = Update_4(keyrow, 1);
                    break;
                case SDLK_e:
                    exit(0);
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
            if (check) loadMedia_4(keyrow, fsize, gRenderer, gTextTexture_3);
            gTextTexture_3[0].render(gRenderer, h, w); w += 70;
            for (int i = 1; i < 9; ++ i)
            {
                gTextTexture_3[i].render(gRenderer, h + 100, w );
                w += sum;
            }
            gTextTexture_3[9].render(gRenderer, h + 550, w + 50 );
            gTextTexture_3[10].render(gRenderer, h, w + 30 );
        }
        else
        {
            for (int i = 0; i < 11; i++)
                gTextTexture_3[i].close();
        }
        SDL_RenderPresent( gRenderer );
    }
}
void Solution(int &check_mixer, int &check_background, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont, Mix_Music *&gMusic)
{
    bool quit = false;
    int next = 0, keyrow = 0, fsize = 40;
    LTexture *gTextTexture_4 = new LTexture[15];
    SDL_Event e;
    loadMedia_1(gRenderer, Bg);

    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    loadMedia_6(keyrow, fsize, gRenderer, gTextTexture_4);

    while( !quit )
    {
        int h = 200, w = 150, sum = 70;
        int check = 0;
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
                switch( e.key.keysym.sym )
                {
                case SDLK_UP:
                    check = 1, keyrow = Update_3(keyrow, -1);
                    break;
                case SDLK_DOWN:
                    check = 1, keyrow = Update_3(keyrow, 1);
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
                loadMedia_1(gRenderer, Bg);
                SDL_RenderClear(gRenderer);
                check = 1;
            }
            if (keyrow == 2)
            {
                S_music(check_mixer, gRenderer, Bg, gFont, gMusic);
                loadMedia_1(gRenderer, Bg);
                SDL_RenderClear(gRenderer);
                check = 1;
            }
            if (keyrow == 3) quit = 1;
            next = 0;

        }


        Bg.render(gRenderer, 0, 0, &background);

        if (quit == 0)
        {
            if (check) loadMedia_6(keyrow, fsize, gRenderer, gTextTexture_4);
            for (int i = 0; i < 3; ++ i)
            {
                gTextTexture_4[i].render(gRenderer, h, w );
                w += sum;
            }
        }
        else
        {
            for (int i = 0; i < 3; i++)
                gTextTexture_4[i].close();
        }
        SDL_RenderPresent( gRenderer );
    }
}
void S_background(int &check_background, SDL_Renderer *&gRenderer, LTexture Bg, TTF_Font *gFont)
{
    bool quit = false;
    int next = 0, keyrow = 0, fsize = 40;
    LTexture *gTextTexture_6 = new LTexture[5];
    SDL_Event e;
    loadMedia_1(gRenderer, Bg);
    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    loadMedia_8(keyrow, fsize, gRenderer, gTextTexture_6);

    while( !quit )
    {
        int h = 200, w = 150, sum = 70;
        int check = 0;
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
                switch( e.key.keysym.sym )
                {
                case SDLK_UP:
                    check = 1, keyrow = Update_5(keyrow, -1);
                    break;
                case SDLK_DOWN:
                    check = 1, keyrow = Update_5(keyrow, 1);
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
                Bg.loadfromfile(gRenderer, "Jungle.png");
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);
            }
            if (keyrow == 2)
            {
                check_background = 2;
                Bg.loadfromfile(gRenderer, "ocean.png");
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);
            }
            if (keyrow == 3)
            {
                check_background = 3;
                Bg.loadfromfile(gRenderer, "galaxy.png");
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
                SDL_RenderClear(gRenderer);
            }
            if (keyrow == 4) quit = 1;
            next = 0;

        }
        if (quit == 0)
        {
            if (check) loadMedia_8(keyrow, fsize, gRenderer, gTextTexture_6);
            Bg.render(gRenderer, 0, 0, &background);
            for (int i = 0; i < 4; ++ i)
            {
                gTextTexture_6[i].render(gRenderer, h, w );
                w += sum;
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                gTextTexture_6[i].close();
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
    LTexture *gTextTexture_7 = new LTexture[5];
    SDL_Event e;
    loadMedia_1(gRenderer, Bg);
    SDL_Rect background = {0, 0, Width, Height};
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);
    loadMedia_9(keyrow, fsize, gRenderer, gTextTexture_7);

    while( !quit )
    {
        int h = 200, w = 150, sum = 70;
        int check = 0;
        while( SDL_PollEvent( &e ) != 0 )
            if( e.type == SDL_KEYDOWN )
                switch( e.key.keysym.sym )
                {
                case SDLK_UP:
                    check = 1, keyrow = Update_5(keyrow, -1);
                    break;
                case SDLK_DOWN:
                    check = 1, keyrow = Update_5(keyrow, 1);
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
                loadMedia_5(check_mixer, gMusic);
                Mix_PlayMusic( gMusic, -1 );
            }
            if (keyrow == 2)
            {
                check_mixer = 2;
                loadMedia_5(check_mixer, gMusic);
                Mix_PlayMusic( gMusic, -1 );
            }
            if (keyrow == 3)
            {
                check_mixer = 3;
                loadMedia_5(check_mixer, gMusic);
                Mix_PlayMusic( gMusic, -1 );
            }
            if (keyrow == 4) quit = 1;
            next = 0;

        }
        if (quit == 0)
        {
            Bg.render(gRenderer, 0, 0, &background);
            if (check) loadMedia_9(keyrow, fsize, gRenderer, gTextTexture_7);
            for (int i = 0; i < 4; ++ i)
            {
                gTextTexture_7[i].render(gRenderer, h, w );
                w += sum;
            }
            SDL_RenderPresent(gRenderer);
        }
        else
        {
            Bg.render(gRenderer, 0, 0, &background);
            for (int i = 0; i < 4; ++ i)
            {
                gTextTexture_7[i].close();
            }
            SDL_RenderPresent(gRenderer);
        }
    }
}
