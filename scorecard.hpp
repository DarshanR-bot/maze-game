#ifndef SCORE_H
#define SCORE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
using namespace std;

class Scorecard{
    public: 
        SDL_Rect *rect1;
        SDL_Rect *rect2;
        SDL_Rect *rect3;
        SDL_Surface *surface[11];
        
        Scorecard(int x,int y){

            rect1 = new SDL_Rect;
            rect2 = new SDL_Rect;
            rect3 = new SDL_Rect;
            rect1->w = 50;
            rect1->h = 50;
            rect1 -> x = x+130;
            rect1 -> y = y;
            rect2->w = 50;
            rect2->h = 50;
            rect2 -> x = x+180;
            rect2 -> y = y;
            rect3->w = 130;
            rect3->h = 50;
            rect3 -> x = x;
            rect3 -> y = y;
            surface[10]=SDL_LoadBMP("scorecard.bmp");
            for(int i=0;i<10;i++){
                surface[i] = SDL_LoadBMP(("score"+to_string(i)+".bmp").c_str());
            }
        }

        void draw(string number, SDL_Surface* screenSurface, SDL_Window* window){
            SDL_BlitSurface(surface[(int)number[0]-48], NULL, screenSurface, rect1);
            SDL_BlitSurface(surface[(int)number[1]-48], NULL, screenSurface, rect2);
            SDL_BlitSurface(surface[10], NULL, screenSurface, rect3);
            SDL_UpdateWindowSurface(window);
        }
};

#endif