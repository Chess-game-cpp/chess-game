#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "./Window.hpp"
using namespace std;
GameScreen::GameScreen(){
    win=nullptr;
  

}
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
            SDL_SetRenderDrawColor(r, 0, 132, 255, 255);
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
    SDL_Surface * image=IMG_Load("assets/pieces.png");
    texture=SDL_CreateTextureFromSurface(win->render,image);
        render();
    }

void GameScreen::render(){
        create_chess_board();
        ChessPiece p;
       
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                p=(game.get_board())->chessBoard[i][j];
                if(p.rank!=0){
              
                    
                        render_chesspiece(i,j,abs(p.rank-6),p.color);
                }
        

            }
        }
      
    SDL_RenderPresent(win->render);
        
    }
    void GameScreen::render_chesspiece(int x,int y,int rank,int color){
           SDL_Rect rect,rect2;
 


         rect.x=80*(rank);
         rect.y=color * 80;
         rect.w=80;
         rect.h=80;
         rect2.x=win->offsetX+(y*(win->size/8));
         rect2.y=win->offsetY+(x*(win->size/8));
         rect2.w=win->size/8;
         rect2.h=win->size/8;
        SDL_RenderCopy(win->render,texture,&rect,&rect2);
         
    }

