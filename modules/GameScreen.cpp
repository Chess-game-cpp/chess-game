#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "./Window.hpp"
using namespace std;
GameScreen::GameScreen()
{
//Default constructor 
    win = nullptr;
    dragging = false;
}
void GameScreen::create_chess_board()
{
    //update the size of board and offset to show in screen
    win->size = win->width > win->height ? win->height : win->width;
    win->offsetX = win->width > win->height ? (win->width - win->height) / 2 : 0;
    win->offsetY = win->width < win->height ? (win->height - win->width) / 2 : 0;
    //create 8x8 chessboard 
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            //render rectangle at required position
            create_rectangle(i, j, win->render, 0);
        }
    }
}
void GameScreen::create_rectangle(int x, int y, SDL_Renderer *&r, int color = 0)
{
    //create rectangele in screen
    SDL_Rect rect;
    //calculating rect based on screen size and square positions [x,y]
    rect.x = x * (win->size / 8) + win->offsetX;
    rect.y = y * (win->size / 8) + win->offsetY;
    rect.w = (win->size / 8);
    rect.h = (win->size / 8);
    //support alpha
    SDL_SetRenderDrawBlendMode(win->render, SDL_BLENDMODE_BLEND);
    //set render_draw_color based on color parameter
    if (color == 0)
    {
        //board color
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
    }
    else if (color == 1)
    {
        //selected piece
        SDL_SetRenderDrawColor(r, 0, 0, 0, 140);
    }
    else if (color == 2)
    {
        //available move
        SDL_SetRenderDrawColor(r, 0, 255, 0, 140);
    }
    else if (color == 3)
    {
        //available capture
        SDL_SetRenderDrawColor(r, 255, 0, 0, 140);
    }
    else if (color == 4)
    {
        //checkmate
        SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
    }
    else if (color == 5)
    {
        //king capture
        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    }
    else if (color == 6)
    {
        //pawn promotion rect
        SDL_SetRenderDrawColor(r, 240, 240, 240, 255);
    }
    SDL_RenderFillRect(r, &rect); // create_rect
    //reset render color
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
}
GameScreen::GameScreen(Window *win)
{
    this->win = win;
    render();
}
void GameScreen::set_window(Window *win)
{
    //set window for screen and load assets
    this->win = win;
    SDL_Surface *image = IMG_Load("assets/pieces.png");
    texture = SDL_CreateTextureFromSurface(win->render, image);
    SDL_FreeSurface(image);
    render();
}
void GameScreen::render()
{
    //clear the renderer
    SDL_RenderClear(win->render);
    //create board in screen
    create_chess_board();
    ChessPiece p;
    
    if (game.get_gameState() == 1)
    {
        //if current gameState is idle
        //check if checkmate
        if (game.is_checkmate())
        {
            //if checkmate show at board by blue rectangle
            Box b = game.get_board()->get_king_position(game.get_board()->currentTurn);
            create_rectangle(b.y, b.x, win->render, 4);
        }
    }
    else if (game.get_gameState() == 0)
    {
        //if game has ended 
        //check if checkmate
        if (game.is_checkmate())
        {
             //if checkmate show at board by blue rectangle
            Box b = game.get_board()->get_king_position(game.get_board()->currentTurn);
            create_rectangle(b.y, b.x, win->render, 5);
        }
    }

    else if (game.get_gameState() == 2)
    {
        //if selection mode
        //grey rect for selected piece
        create_rectangle((game.get_currentChecePiece())->position.y, (game.get_currentChecePiece())->position.x, win->render, 1);
        for (int i = 0; i < (game.get_currentChecePiece())->totalmoves; i++)
        {
            //loop through moves of selected piece
            if (((game.get_board())->chessBoard[(game.get_currentChecePiece())->moves[i].x][(game.get_currentChecePiece())->moves[i].y]).rank > 0)
            {

                //red if move captures the opponents piece
                create_rectangle((game.get_currentChecePiece())->moves[i].y, (game.get_currentChecePiece())->moves[i].x, win->render, 3);
            }
            else
            {
                //green if move is legal
                create_rectangle((game.get_currentChecePiece())->moves[i].y, (game.get_currentChecePiece())->moves[i].x, win->render, 2);
            }
        }
    }
    //render chess piece in the board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            p = (game.get_board())->chessBoard[i][j];
            //check if current index [i,j] holds any piece
            if (p.rank != 0)
            {
               //if dragging the piece avoid rendering it
                if (game.get_gameState() == 2 && dragging == true && i == game.get_currentChecePiece()->position.x && j == game.get_currentChecePiece()->position.y)
                    continue;
                //render chess piece
                render_chesspiece(win->offsetY + (i * (win->size / 8)), win->offsetX + (j * (win->size / 8)), abs(p.rank - 6), p.color);
            }
        }
    }
    if (dragging && game.get_gameState() == 2)
    {
        //render the piece that is dragging in screen
        render_chesspiece(mousePos.x - (win->size / 16), mousePos.y - (win->size / 16), abs(game.get_currentChecePiece()->rank - 6), game.get_currentChecePiece()->color);
    }
    //check for pawn promotion
    if (game.get_gameState() == 3)
    {
        // pawnpromotion query
        //render chess peice for query
        for (int i = 0; i < 4; i++)
        {
            int x = game.get_currentMove()->y;
            int y = ((game.get_currentMove()->x / 7) * 4) + i;
            create_rectangle(x, y, win->render, 6);
            render_chesspiece(win->offsetY + (y * (win->size / 8)), win->offsetX + (x * (win->size / 8)), abs(i + 2 - 6), game.get_currentChecePiece()->color);
        }
    }
    //render window
    SDL_RenderPresent(win->render);
}
void GameScreen::render_chesspiece(int x, int y, int rank, int color)
{
    //Function to render chess piece
    //rect to capture the required piece from the image
    //rect2 to place the piece in screen
    SDL_Rect rect, rect2;

    rect.x = 80 * (rank);
    rect.y = color * 80;
    rect.w = 80;
    rect.h = 80;
    rect2.x = y;
    rect2.y = x;
    rect2.w = win->size / 8;
    rect2.h = win->size / 8;
    //render the piece in screen
    SDL_RenderCopy(win->render, texture, &rect, &rect2);
}
void GameScreen::event_handle(SDL_Event &e)
{
//handle events in Game Screen
    int x, y;

    switch (e.type)
    {
    case SDL_MOUSEBUTTONDOWN:

        SDL_GetMouseState(&x, &y);
        mousePos.x = y;
        mousePos.y = x;
        x = (x - win->offsetX) / (win->size / 8);
        y = (y - win->offsetY) / (win->size / 8);

        if (game.get_gameState() == 3)
        {
            // pawn promotion handler
            //check if promoted chess piece is selected
            for (int i = 0; i < 4; i++)
            {
                int m = game.get_currentMove()->y;
                int n = ((game.get_currentMove()->x / 7) * 4) + i;
                if (m == x && n == y)
                {
                    //promote pawn
                    game.promote_pawn(i + 2);
                    break;
                }
            }
            render();
            break;
        }
        //check if clicked inside the board
        if (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
            //check if piece is dragging in the screen
            if (dragging)
                break;
            //move the chess piece
            if (game.get_gameState() == 2)
            {
                game.piece_move(y, x);
            }
            //select the chess piece
            else if (game.get_gameState() == 1)
            {
                game.piece_selection(x, y);
            }
            //another chess piece dragging::"Moved position is another chess Piece position"
            if (game.get_gameState() == 2)
            {
                dragging = true;
            }
        }
        render();

        break;
    case SDL_MOUSEBUTTONUP:
    //check if piece was dragging
        if (dragging)
        {
            dragging = false;
            SDL_GetMouseState(&x, &y);
            mousePos.x = y;
            mousePos.y = x;
            x = (x - win->offsetX) / (win->size / 8);
            y = (y - win->offsetY) / (win->size / 8);
            //check if clicked inside the board
            if (x >= 0 && x < 8 && y >= 0 && y < 8)
            {
                if (game.get_currentChecePiece()->position == Box(y, x))
                {
                    //select the chess piece instead of dragging
                }
                else
                {
                    //move chess piece if legal 
                    game.piece_move(y, x, false);
                }
            }
            render();
            break;
        }

    case SDL_MOUSEMOTION:
      //check if piece is dragging
        if (dragging)
        {
            SDL_GetMouseState(&x, &y);
            mousePos.x = y;
            mousePos.y = x;

            x = (x - win->offsetX) / (win->size / 8);
            y = (y - win->offsetY) / (win->size / 8);

            if (x >= 0 && x < 8 && y >= 0 && y < 8)
            {
            }
            else
            {
                //if mouse cursor is outside board abort the dragging
                game.piece_selection(9, 0);
                dragging = false;
            }
            render();
        }
        break;
    default:
        break;
    }
}