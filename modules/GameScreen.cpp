#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./Window.hpp"
using namespace std;

GameScreen::GameScreen(Window *win, int time)
{
    // Default constructor
    modal_active = false;
    this->win = win;
    rendering = false;
    dragging = false;
    // set count_down timer
    timer.set_timer(time);
    // if timer is initialized
    if (timer.is_active())
    {
        timer.set_id(SDL_AddTimer(TIMER, timer_update, (void *)(this)));
    }
    // load assets and render
    load_assets();
    modal.init(win->render, 0, 0, dim::width, dim::height);
    game.init_game();
    render();
}

void GameScreen::create_chess_board()
{

    // create 8x8 chessboard
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // render rectangle at required position
            create_rectangle(i, j, win->render, 0);
        }
    }
}
void GameScreen::create_rectangle(int x, int y, SDL_Renderer *&r, int color = 0)
{
    // create rectangele in screen
    SDL_Rect rect;
    // calculating rect based on screen size and square positions [x,y]
    rect.x = x * dim::size;
    rect.y = y * dim::size;
    rect.w = dim::size;
    rect.h = dim::size;
    // support alpha
    SDL_SetRenderDrawBlendMode(win->render, SDL_BLENDMODE_BLEND);
    // set render_draw_color based on color parameter
    if (color == 0)
    {
        // board color
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
        // selected piece
        SDL_SetRenderDrawColor(r, 0, 0, 0, 140);
    }
    else if (color == 2)
    {
        // available move
        SDL_SetRenderDrawColor(r, 0, 255, 0, 140);
    }
    else if (color == 3)
    {
        // available capture
        SDL_SetRenderDrawColor(r, 255, 0, 0, 140);
    }
    else if (color == 4)
    {
        // checkmate
        SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
    }
    else if (color == 5)
    {
        // king capture
        SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    }
    else if (color == 6)
    {
        // pawn promotion rect
        SDL_SetRenderDrawColor(r, 240, 240, 240, 255);
    }
    SDL_RenderFillRect(r, &rect); // create_rect
    // reset render color
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
}

void GameScreen::load_assets()
{
    // load assets
    // chesspieces
    SDL_Surface *image = IMG_Load("assets/pieces.png");
    texture = SDL_CreateTextureFromSurface(win->render, image);
    image = IMG_Load("assets/bg.png");
    btexture = SDL_CreateTextureFromSurface(win->render, image);
    load_other();
    SDL_FreeSurface(image);
}
void GameScreen::load_other(){

    SDL_Surface *image = IMG_Load("assets/timer.png");
    timer_texture = SDL_CreateTextureFromSurface(win->render, image);

    exitbtn.init(win->render, "assets/exit.png", dim::height + (dim::sidebar - 139) / 2, 430);
    resbtn.init(win->render, "assets/restart.png", dim::height + (dim::sidebar - 139) / 2, 430 + 55);
    SDL_FreeSurface(image);
}
void GameScreen::render()
{
    if (rendering)
        return;
    rendering = true;
    SDL_SetRenderDrawColor(win->render, 255, 255, 255, 255);
    // clear the renderer
    SDL_RenderClear(win->render);
   //render game_assets
    render_chessgame();
    // sidebar
    render_sidebar();

    
    // render modal

    if (modal_active)
    {
        modal.render(win->render);
    }
    SDL_RenderPresent(win->render);
    rendering = false;
}
std::string GameScreen::mstotime(int ms)
{
    int second = ms / 1000;
    int min = second / 60;
    second = second % 60;
    std::string txt = (min < 10 ? "0" : "") + to_string(min) + ":" + (second < 10 ? "0" : "") + to_string(second);
    return txt;
}
void GameScreen::render_chessgame(){
     // create board in screen
    create_chess_board();
    ChessPiece p;

    if (game.get_gameState() == 1 || game.get_gameState() == 4)
    {
        // if current gameState is idle
        // check if checkmate
        if (game.is_checkmate())
        {
            // if checkmate show at board by blue rectangle
            Box b = game.get_king_position(game.get_turn());
            create_rectangle(b.y, b.x, win->render, 4);
        }
    }
    else if (game.get_gameState() == 0)
    {
        // if game has ended
        // check if checkmate
        if (game.is_checkmate())
        {
            // if checkmate show at board by blue rectangle
            Box b = game.get_king_position(game.get_turn());
            create_rectangle(b.y, b.x, win->render, 5);
        }
    }

    else if (game.get_gameState() == 2)
    {
        // if selection mode
        // grey rect for selected piece
        create_rectangle((game.get_currentChessPiece())->get_position().y, (game.get_currentChessPiece())->get_position().x, win->render, 1);
        for (int i = 0; i < (game.get_currentChessPiece())->totalmoves; i++)
        {
            // loop through moves of selected piece
            if ((game.get_chesspiece((game.get_currentChessPiece())->get_moves()[i].x, (game.get_currentChessPiece())->get_moves()[i].y)).get_rank() > 0)
            {

                // red if move captures the opponents piece
                create_rectangle((game.get_currentChessPiece())->get_moves()[i].y, (game.get_currentChessPiece())->get_moves()[i].x, win->render, 3);
            }
            else
            {
                // green if move is legal
                create_rectangle((game.get_currentChessPiece())->get_moves()[i].y, (game.get_currentChessPiece())->get_moves()[i].x, win->render, 2);
            }
        }
    }
    // render chess piece in the board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            p = game.get_chesspiece(i, j);
            // check if current index [i,j] holds any piece
            if (p.get_rank() != 0)
            {
                // if dragging the piece avoid rendering it
                if (game.get_gameState() == 2 && dragging == true && i == game.get_currentChessPiece()->get_position().x && j == game.get_currentChessPiece()->get_position().y)
                    continue;
                // render chess piece
                render_chesspiece((i * dim::size), (j * dim::size), abs(p.get_rank() - 6), p.get_color());
            }
        }
    }
    if (dragging && game.get_gameState() == 2)
    {
        // render the piece that is dragging in screen
        render_chesspiece(mousePos.x - dim::size / 2, mousePos.y - dim::size / 2, abs(game.get_currentChessPiece()->get_rank() - 6), game.get_currentChessPiece()->get_color());
    }
    // check for pawn promotion
    if (game.get_gameState() == 3)
    {
        // pawnpromotion query
        // render chess peice for query
        for (int i = 0; i < 4; i++)
        {
            int x = game.get_currentMove()->y;
            int y = ((game.get_currentMove()->x / 7) * 4) + i;
            create_rectangle(x, y, win->render, 6);
            render_chesspiece((y * dim::size), (x * dim::size), abs(i + 2 - 6), game.get_currentChessPiece()->get_color());
        }
    }
}
void GameScreen::render_sidebar(){
    //render background
    SDL_Rect rec2;
    rec2.x = 0;
    rec2.y = 0;
    rec2.h = dim::height;
    rec2.w = dim::sidebar;

    SDL_Rect rec3;
    rec3.x = dim::height;
    rec3.y = 0;
    rec3.h = dim::height;
    rec3.w = dim::sidebar;

    SDL_RenderCopy(win->render, btexture, &rec2, &rec3);
    // rendeer player detaisl
    SDL_Color BLACK = {0, 0, 0, 255};
    for (int i = 0; i < 2; i++)
    {
        int lx = dim::height + 10;
        int ly = 10 + (i ? 550 : 0);
        // player name
        SDL_Rect prect;
        prect.x = lx;
        prect.y = ly;
        TextureManager::set_font("assets/BebasNeue.ttf", 30);
        TextureManager::render_text((i ? "Player 1" : "Player2"), BLACK, win->render, prect);
        if (timer.is_active())
        {
            prect.x = lx;
            prect.y = ly;
            prect.w = dim::sidebar - 20;
            TextureManager::render_text(mstotime(timer.get_time(!i)).c_str(), BLACK, win->render, prect, 0, 2);
            prect.h = 35;
            prect.w = 35;
            prect.y += (TextureManager::height / 2) - (prect.h / 2) - 4;
            prect.x -= prect.w + 4;
            SDL_RenderCopy(win->render, timer_texture, NULL, &prect);
        }
        ly += 30;
        for (int j = 0; j < 16; j++)
        {
            ChessPiece &cp = game.get_captured(i)[j];
            if (cp.get_rank() == 0)
            {
                break;
            }

            render_chesspiece(ly, lx, 6 - cp.get_rank(), cp.get_color(), (dim::sidebar - 10) / 8);
            lx += (dim::sidebar - 10) / 8;
            if (j == 7)
            {
                lx = dim::height + 10;
                ly = ly + (dim::sidebar - 10) / 8;
            }
        }
    }

    // render_info
    SDL_Rect turn;
    turn.x = dim::height;
    turn.y = ((dim::height) / 2) - 25;
    turn.w = dim::sidebar;
    std::string text;
    if (game.get_gameState() == 4)
    {
        text = game.get_turn() ? "Black Won" : "White Won";
        TextureManager::render_text("TIME'S UP!!", BLACK, win->render, turn, 0, 1);
        //"Black Won" White Won
        // Time's Up
    }
    else if (game.get_gameState() == 0)
    {
        text = game.is_checkmate() ? (!game.get_turn() ? "Black Won" : "White Won") : "Match Drawn";
        // "Black Won" White Won
        // Match Draw
    }
    else
    {
        text = !game.get_turn() ? "White's Turn" : "Black's Turn";
        if (game.is_checkmate())
        {

            TextureManager::render_text("CHECKMATE!!", BLACK, win->render, turn, 0, 1);
        }
        // Black's turn
        // checkmatee
    }
    turn.x = dim::height;
    turn.y = ((dim::height) / 2) - 60;
    turn.w = dim::sidebar;
    TextureManager::render_text(text, BLACK, win->render, turn, 0, 1);
    // render buttons
    exitbtn.render(win->render);
    resbtn.render(win->render);
}
void GameScreen::render_chesspiece(int x, int y, int rank, int color, int size)
{
    // Function to render chess piece
    // rect to capture the required piece from the image
    // rect2 to place the piece in screen
    SDL_Rect rect, rect2;

    rect.x = 80 * (rank);
    rect.y = color * 80;
    rect.w = 80;
    rect.h = 80;
    rect2.x = y;
    rect2.y = x;
    rect2.w = size;
    rect2.h = size;
    // render the piece in screen
    SDL_RenderCopy(win->render, texture, &rect, &rect2);
}
void GameScreen::event_handle(SDL_Event &e)
{
    // handle events in Game Screen
    int x, y;
 
    switch (e.type)
    {
    case SDL_MOUSEBUTTONDOWN:

        SDL_GetMouseState(&x, &y);
        mousePos.x = y;
        mousePos.y = x;
        if (modal_active)
        {
            if (modal.is_Clicked(x, y))
            {
                modal_handler();
            }
            render();
            break;
        }

        if (x > dim::height)
        {
           if(button_handler())break;
        }
        x = (x) / (dim::size);
        y = (y) / (dim::size);
        // button_click handling

        if (game.get_gameState() == 3)
        {
            // pawn promotion handler
            // check if promoted chess piece is selected
            for (int i = 0; i < 4; i++)
            {
                int m = game.get_currentMove()->y;
                int n = ((game.get_currentMove()->x / 7) * 4) + i;
                if (m == x && n == y)
                {
                    // promote pawn
                    game.promote_pawn(i + 2);
                    break;
                }
            }
            render();
            break;
        }
        // check if clicked inside the board
        if (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
            // check if piece is dragging in the screen
            if (dragging)
                break;
            // move the chess piece
            if (game.get_gameState() == 2)
            {
                game.piece_move(y, x);
            }
            // select the chess piece
            else if (game.get_gameState() == 1)
            {
                game.piece_selection(x, y);
            }
            // another chess piece dragging::"Moved position is another chess Piece position"
            if (game.get_gameState() == 2)
            {
                dragging = true;
            }
        }
        render();

        break;
    case SDL_MOUSEBUTTONUP:
        // check if piece was dragging
        if (dragging)
        {
            dragging = false;
            SDL_GetMouseState(&x, &y);
            mousePos.x = y;
            mousePos.y = x;
            x = (x) / (dim::size);
            y = y / (dim::size);
            // check if clicked inside the board
            if (x >= 0 && x < 8 && y >= 0 && y < 8)
            {
                if (game.get_currentChessPiece()->get_position() == Box(y, x))
                {
                    // select the chess piece instead of dragging
                }
                else
                {
                    // move chess piece if legal
                    game.piece_move(y, x, false);
                }
            }
            render();
            break;
        }

    case SDL_MOUSEMOTION:
        // check if piece is dragging

        if (dragging)
        {
            if (game.get_gameState() == 4)
            {
                dragging = false;
                render();
                break;
            }
            SDL_GetMouseState(&x, &y);
            mousePos.x = y;
            mousePos.y = x;

            x = (x) / (dim::size);
            y = (y) / (dim::size);

            if (x >= 0 && x < 8 && y >= 0 && y < 8)
            {
            }
            else
            {
                // if mouse cursor is outside board abort the dragging
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
