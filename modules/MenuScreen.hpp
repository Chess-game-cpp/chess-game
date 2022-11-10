#pragma once
#include <iostream>
#include "Window.hpp"
#include "Screen.hpp"
#include "Component.cpp"
#include <SDL2/SDL.h>
class MenuScreen : public Screen
{
    Button gameMode;
    Button puzzleMode;
    Button exit;
    SDL_Texture *bgtexture;
    

public:
    MenuScreen(Window *);
    ~MenuScreen()
    {
        SDL_DestroyTexture(bgtexture);
    }
    void render();
    void event_handle(SDL_Event &);
};
class GameOptionScreen : public Screen
{
    Button goBack;
    Button startGame;
    ButtonGroup <2> players;
    ButtonGroup <4> limits;
    SDL_Texture * bgtexture;
    public:
    GameOptionScreen(Window *);
    ~GameOptionScreen(){
        SDL_DestroyTexture(bgtexture);
    }
   void render();
    void event_handle(SDL_Event &);  

};