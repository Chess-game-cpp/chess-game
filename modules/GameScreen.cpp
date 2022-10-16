#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "./Window.hpp"
using namespace std;
void GameScreen::create_chess_board()
    {
        win->size=win->width>win->height?win->height:win->width;
        win->offsetX=win->width>win->height?(win->width-win->height)/2:0 ;
        win->offsetY=win->width<win->height?(win->height-win->width)/2:0 ;
        SDL_RenderClear(win->render);
           SDL_RenderPresent(win->render);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                create_rectangle(i, j, win->render);
            }
        }
         
    }
  void GameScreen::create_rectangle(int x, int y, SDL_Renderer *&r)
    {

        SDL_Rect rect;

        rect.x = x * (win->size / 8)+win->offsetX;
        rect.y = y * (win->size / 8)+win->offsetY;
        rect.w = (win->size / 8);
        rect.h = (win->size / 8);
        if ((x + y) % 2 == 1)
        {
            // even =black
            SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
            // odd = white
        }
        // SDL_SetRenderDrawColor(r, 0, 255, 255,255);
        SDL_RenderFillRect(r, &rect); // create_rect
    }
  GameScreen::GameScreen(Window *win){
        this->win=win;
        render();
    }
  void GameScreen::set_window(Window *win){
        this->win=win;
        render();
    }

void GameScreen::render(){
        create_chess_board();
        SDL_Surface * image=IMG_Load("assets/pieces.png");
        texture=SDL_CreateTextureFromSurface(win->render,image);
         SDL_Rect rect,rect2;
         for(int i=0;i<6;i++){


         rect.x=80*i;
         rect.y=0;
         rect.w=80;
         rect.h=80;
         rect2.x=win->offsetX+(i*(win->size/8));
         rect2.y=win->offsetY;
         rect2.w=win->size/8;
         rect2.h=win->size/8;
        SDL_RenderCopy(win->render,texture,&rect,&rect2);
         }
    SDL_RenderPresent(win->render);
        
    }

