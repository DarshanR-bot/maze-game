#ifndef MESSAGE_H
#define MESSAGE_H
#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class Message{
    public:
        SDL_Rect* rect;
        SDL_Surface* surface[10];
        
        Message(int x,int y){
            rect = new SDL_Rect;
            rect->w = 100;
            rect->h = 60;
            rect->x = x;
            rect->y = y;
            for(int i=0;i<10;i++){
                surface[i] = SDL_LoadBMP(("message"+to_string(i)+".bmp").c_str());
            }
        }

        void draw(int count, SDL_Surface* screenSurface, SDL_Window* window){
            SDL_BlitSurface(surface[count], NULL, screenSurface, rect);
            SDL_UpdateWindowSurface(window);
        }
};

#endif