#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "./Screen.hpp"
#include "./Engine.hpp"
using namespace std;
class GameScreen : public Screen
{
    Engine game;
    SDL_Texture *texture;
    bool dragging;
    Box mousePos;

public:
    GameScreen(Window *);
    GameScreen();
    void set_window(Window *);
    void render();
    void event_handle(SDL_Event &);

    void create_chess_board();
    void create_rectangle(int, int, SDL_Renderer *&,int);
    void render_chesspiece(int, int, int, int);
};
