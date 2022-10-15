#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "./Screen.hpp"
using namespace std;
class GameScreen : public Screen
{
    public:
    GameScreen(Window *);
    GameScreen(){
        win=nullptr;
    }
    void set_window(Window *);
    void render(){
        create_chess_board();
    }
    void event_handle(){
        // create_chess_board();

    }
    void create_chess_board();
    void create_rectangle(int,int,SDL_Renderer*&);
       
};
