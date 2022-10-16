#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "./Window.hpp"
using namespace std;
GameScreen::GameScreen()
{
    win = nullptr;
}
void GameScreen::create_chess_board()
{
    win->size = win->width > win->height ? win->height : win->width;
    win->offsetX = win->width > win->height ? (win->width - win->height) / 2 : 0;
    win->offsetY = win->width < win->height ? (win->height - win->width) / 2 : 0;
    // SDL_RenderClear(win->render);
    SDL_RenderPresent(win->render);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {

            create_rectangle(i, j, win->render,0);
        }
    }
}
void GameScreen::create_rectangle(int x, int y, SDL_Renderer *&r,int color=0)
{

    SDL_Rect rect;

    rect.x = x * (win->size / 8) + win->offsetX;
    rect.y = y * (win->size / 8) + win->offsetY;
    rect.w = (win->size / 8);
    rect.h = (win->size / 8);
    SDL_SetRenderDrawBlendMode(win->render, SDL_BLENDMODE_BLEND);
    if(color==0){
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
        
    }else if(color==1){
        SDL_SetRenderDrawColor(r, 0, 0, 0, 140);

    }else if(color==2){
        SDL_SetRenderDrawColor(r, 0, 255, 0, 140);

    }
    else if(color==3){
        SDL_SetRenderDrawColor(r, 255, 0, 0, 140);

    }
    else if(color==4){
        SDL_SetRenderDrawColor(r, 0, 0, 255, 255);

    }
    else if(color==5){
        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);

    }
    // SDL_SetRenderDrawColor(r, 0, 255, 255,255);
    SDL_RenderFillRect(r, &rect); // create_rect
}
GameScreen::GameScreen(Window *win)
{
    this->win = win;
    render();
}
void GameScreen::set_window(Window *win)
{
    this->win = win;
    SDL_Surface *image = IMG_Load("assets/pieces.png");
    texture = SDL_CreateTextureFromSurface(win->render, image);
    render();
}

void GameScreen::render()
{

    create_chess_board();
    //running
    ChessPiece p;
    if(game.get_gameState()==1){
      if(game.is_checkmate()){
                Box b=game.get_board()->get_king_position(game.get_board()->currentTurn);
        create_rectangle(b.y,b.x,win->render,4);
                
            }
    }
    else if (game.get_gameState()==0){
     if(game.is_checkmate()){
                   Box b=game.get_board()->get_king_position(game.get_board()->currentTurn);
        create_rectangle(b.y,b.x,win->render,5);
     }   
    }

    else if(game.get_gameState()==2){
        if(game.is_checkmate()){
                Box b=game.get_board()->get_king_position(game.get_board()->currentTurn);
        create_rectangle(b.y,b.x,win->render,4);
                
            }

        create_rectangle((game.get_currentChecePiece())->position.y,(game.get_currentChecePiece())->position.x,win->render,1);
        for(int i=0;i<(game.get_currentChecePiece())->totalmoves;i++){
         if(((game.get_board())->chessBoard[(game.get_currentChecePiece())->moves[i].x][(game.get_currentChecePiece())->moves[i].y]).rank>0){

        create_rectangle((game.get_currentChecePiece())->moves[i].y,(game.get_currentChecePiece())->moves[i].x,win->render,3);
            }else{
        create_rectangle((game.get_currentChecePiece())->moves[i].y,(game.get_currentChecePiece())->moves[i].x,win->render,2);

            }


        }
           
    }
for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            p = (game.get_board())->chessBoard[i][j];
            if (p.rank != 0)
            {

                render_chesspiece(i, j, abs(p.rank - 6), p.color);
            }
        }
    }
    SDL_RenderPresent(win->render);
}
void GameScreen::render_chesspiece(int x, int y, int rank, int color)
{
    SDL_Rect rect, rect2;

    rect.x = 80 * (rank);
    rect.y = color * 80;
    rect.w = 80;
    rect.h = 80;
    rect2.x = win->offsetX + (y * (win->size / 8));
    rect2.y = win->offsetY + (x * (win->size / 8));
    rect2.w = win->size / 8;
    rect2.h = win->size / 8;
    SDL_RenderCopy(win->render, texture, &rect, &rect2);
}

void GameScreen::event_handle(SDL_Event &e)
{
    // mouse click event handling
    int x, y;
    switch (e.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&x, &y);
        x = (x - win->offsetX) / (win->size / 8);
        y = (y - win->offsetY) / (win->size / 8);
      
      
         if(game.get_gameState()==2){
            game.piece_move(y,x);
        }else if(game.get_gameState()==1){
        game.piece_selection(x,y);
        }
        render();

        break;
    default:
        break;
    }
}