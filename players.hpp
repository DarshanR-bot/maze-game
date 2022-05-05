#ifndef PLAYERS_HPP
#define PLAYERS_HPP
#include  <SDL2/SDL.h>

#include <bits/stdc++.h>
#include <string>  
#include "tiling.hpp"
#include "texture.hpp"

using namespace std;


class Player
{
    public:
		//Collision box of the dot
		SDL_Rect mBox;

		//The velocity of the dot
		int mVelX, mVelY;
        SDL_Texture *l_s[3],*r_s[3],*u_s[3],*d_s[3];
        SDL_Texture *c_l,*c_r,*c_u,*c_d;
    

		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;
        int count = 0;
        string face = "down";
        bool cycle;
        float energy;
        float health;

		//Maximum axis velocity of the dot
		int DOT_VEL = 3;
        Player(){}
		//Initializes the variables
		Player(SDL_Renderer* gRenderer)
        {
            //Initialize the collision box
            mBox.x = 200;
            mBox.y = 70;
            mBox.w = DOT_WIDTH;
            mBox.h = DOT_HEIGHT;
            cycle = false;
            //Initialize the velocity
            mVelX = 0;
            mVelY = 0;
            loadmedia(gRenderer);
            energy = 1.0;
            health = 1.0;
        }

        void take_yulu(LTexture *gDotTexture){
            cycle = true;
            SDL_Texture* temp;
            if(face=="up")
                temp = c_u;
            else if(face=="down")
                temp = c_d;
            else if(face=="left")
                temp = c_l;
            else if(face=="right")
                temp = c_r;
            gDotTexture->mTexture = temp;

        }

        void leave_yulu(LTexture *gDotTexture){
            cycle = false;
            count = 0;
            SDL_Texture* temp;
            if(face=="up")
                temp = u_s[count];
            else if(face=="down")
                temp = d_s[count];
            else if(face=="left")
                temp = l_s[count];
            else if(face=="right")
                temp = r_s[count];
            gDotTexture->mTexture = temp;
        }

		//Takes key presses and adjusts the dot's velocity
		void handleEvent(SDL_Event &e,LTexture *gDotTexture)
        {
            //If a key was pressed
            if(!cycle){DOT_VEL = 2;}
            else{DOT_VEL = 4;}
            if( e.type == SDL_KEYDOWN )//&& e.key.repeat == 0 )
            {
                if(e.key.repeat == 0){
                //Adjust the velocity
                    switch( e.key.keysym.sym )
                    {
                        case SDLK_UP: mVelY -= DOT_VEL;face = "up"; break;
                        case SDLK_DOWN: mVelY += DOT_VEL;face = "down";break;
                        case SDLK_LEFT: mVelX -= DOT_VEL;face = "left";break;
                        case SDLK_RIGHT: mVelX += DOT_VEL;face = "right";break;
                        case SDLK_RETURN:
                            mVelX +=0;
                            if(yulu.count(pair<int,int>((mBox.x+DOT_WIDTH/2)/32,(mBox.y+ DOT_HEIGHT/2)/32))){
                                if(cycle){cycle = false;}
                                else{cycle = true;}
                            }
                            
                            else if(food.count(pair<int,int>((mBox.x+DOT_WIDTH/2)/32,(mBox.y+DOT_HEIGHT/2)/32))){
                                energy = 1.0;
                                cerr<<"#########################"<<"energy"<<"#########################"<<endl;
                            }
                            else if(hospital.count(pair<int,int>((mBox.x+DOT_WIDTH/2)/32,(mBox.y+DOT_HEIGHT/2)/32))){
                                health = 1.0;
                                cerr<<"#########################"<<"health"<<"#########################"<<endl;
                            }
                            break;
                        default: break;
                    }
                }
                updateData(gDotTexture);
            }
            //If a key was released
            else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
            {
                //Adjust the velocity
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP: mVelY += DOT_VEL;face = "up";break;
                    case SDLK_DOWN: mVelY -= DOT_VEL;face = "down"; break;
                    case SDLK_LEFT: mVelX += DOT_VEL;face = "left";break;
                    case SDLK_RIGHT: mVelX -= DOT_VEL;face = "right";break;
                }
            }    
        }

    
        void loadmedia(SDL_Renderer* gRenderer){
            string image  = "randi";
            for(int i = 0; i < 3; i++){
                l_s[i] = SDL_CreateTextureFromSurface(gRenderer,SDL_LoadBMP((image+to_string(i)+"l.bmp").c_str()));
                r_s[i] = SDL_CreateTextureFromSurface(gRenderer,SDL_LoadBMP((image+to_string(i)+"r.bmp").c_str()));
                u_s[i] = SDL_CreateTextureFromSurface(gRenderer,SDL_LoadBMP((image+to_string(i)+"u.bmp").c_str()));
                d_s[i] = SDL_CreateTextureFromSurface(gRenderer,SDL_LoadBMP((image+to_string(i)+"d.bmp").c_str()));
            }
            image = "cycle";
            c_l = SDL_CreateTextureFromSurface(gRenderer,SDL_LoadBMP((image+"l.bmp").c_str()));
            c_r = SDL_CreateTextureFromSurface(gRenderer,SDL_LoadBMP((image+"r.bmp").c_str()));
            c_u = SDL_CreateTextureFromSurface(gRenderer,SDL_LoadBMP((image+"u.bmp").c_str()));
            c_d = SDL_CreateTextureFromSurface(gRenderer,SDL_LoadBMP((image+"d.bmp").c_str()));
        }


		//Moves the dot and check collision against tiles
		void move( Tile *tiles[])
        {
            //Move the dot left or right
            mBox.x += mVelX;

            //If the dot went too far to the left or right or touched a wall
            if( ( mBox.x < 0 ) || ( mBox.x + DOT_WIDTH > LEVEL_WIDTH ) || touchesWall( mBox, tiles ) )
            {
                //move back
                mBox.x -= mVelX;
            }

            //Move the dot up or down
            mBox.y += mVelY;

            //If the dot went too far up or down or touched a wall
            if( ( mBox.y < 0 ) || ( mBox.y + DOT_HEIGHT > LEVEL_HEIGHT ) || touchesWall( mBox, tiles ) )
            {
                //move back
                mBox.y -= mVelY;
            }


            // if(!cycle){
            //         count++;
            //         count=count%3;
            //         SDL_Texture* temp;
            //         if(face=="up")
            //             temp = u_s[count];
            //         else if(face=="down")
            //             temp = d_s[count];
            //         else if(face=="left")
            //             temp = l_s[count];
            //         else if(face=="right")
            //             temp = r_s[count];
            //         gDotTexture->mTexture = temp;
            //     }
            //     else{
            //         SDL_Texture* temp;
            //         if(face=="up")
            //             temp = c_u;
            //         else if(face=="down")
            //             temp = c_d;
            //         else if(face=="left")
            //             temp = c_l;
            //         else if(face=="right")
            //             temp = c_r;
            //         gDotTexture->mTexture = temp;
            //     }
        }

		//Centers the camera over the dot
		void setCamera( SDL_Rect& camera )
        {
            //Center the camera over the dot
            camera.x = ( mBox.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
            camera.y = ( mBox.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

            //Keep the camera in bounds
            if( camera.x < 0 )
            { 
                camera.x = 0;
            }
            if( camera.y < 0 )
            {
                camera.y = 0;
            }
            if( camera.x > LEVEL_WIDTH - camera.w )
            {
                camera.x = LEVEL_WIDTH - camera.w;
            }
            if( camera.y > LEVEL_HEIGHT - camera.h )
            {
                camera.y = LEVEL_HEIGHT - camera.h;
            }
        }

        void updateData(LTexture* gDotTexture){
            if(!cycle){
                count++;
                count=count%3;
                SDL_Texture* temp;
                if(face=="up")
                    temp = u_s[count];
                else if(face=="down")
                    temp = d_s[count];
                else if(face=="left")
                    temp = l_s[count];
                else if(face=="right")
                    temp = r_s[count];
                gDotTexture->mTexture = temp;
            }
            else{
                SDL_Texture* temp;
                if(face=="up")
                    temp = c_u;
                else if(face=="down")
                    temp = c_d;
                else if(face=="left")
                    temp = c_l;
                else if(face=="right")
                    temp = c_r;
                gDotTexture->mTexture = temp;
            }
        }

		//Shows the dot on the screen
		void render( SDL_Rect& camera, LTexture *gDotTexture ,SDL_Renderer* gRenderer)
        {
            //Show the dot
            
            gDotTexture->render( mBox.x - camera.x, mBox.y - camera.y, gRenderer, NULL);
        }

        string dataToSend(){
            stringstream ss;
            ss << mBox.x << " " << mBox.y << " " << mVelX << " " << mVelY << " " << face << " " << count << " " << cycle;
            return ss.str();
        }

    
};

#endif