#pragma once
#include <iostream>
#include "Window.hpp"
#include "Screen.hpp"
#include "Component.cpp"
#include <SDL2/SDL.h>
class MenuScreen:public Screen{
     Modal modal;
     Box mousePos;
     Button gameMode;
     Button puzzleMode;
     Button exit;
     SDL_Texture *bgtexture;
    public:
MenuScreen(Window * );
~MenuScreen(){
    SDL_DestroyTexture(bgtexture);
}
void render();
void event_handle(SDL_Event & );
};