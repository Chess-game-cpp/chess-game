#pragma once
#include "MenuScreen.hpp"
#include <SDL2/SDL.h>

MenuScreen::MenuScreen(Window * win){
    this->win=win;
    //load background assets
    SDL_Surface *image = IMG_Load("assets/bg.png");
    bgtexture = SDL_CreateTextureFromSurface(win->render, image);
    SDL_FreeSurface(image);
    //initialize modal
    modal.init(win->render,0,0,dim::width,dim::height);

    //initialize Button
    gameMode.init(win->render,"menu1",(dim::width-223)/2,200);
    puzzleMode.init(win->render,"menu2",(dim::width-223)/2,200+125);
    exit.init(win->render,"menu3",(dim::width-223)/2,200+250);
}
void MenuScreen::render(){
    SDL_RenderClear(win->render);
    SDL_Rect rect;
    rect.x=0;
    rect.y=0;
    rect.w=dim::width;
    rect.h=dim::height;
    SDL_RenderCopy(win->render,bgtexture,NULL,&rect);
    gameMode.render(win->render);
    puzzleMode.render(win->render);
    exit.render(win->render);
    if(modal.is_active){
        modal.render(win->render);
    }
    SDL_RenderPresent(win->render);

    
    
}
void MenuScreen::event_handle(SDL_Event & e){
   // handle events in Game Screen
    int x, y;
 
    switch (e.type)
    {
    case SDL_MOUSEBUTTONDOWN:

        SDL_GetMouseState(&x, &y);
        mousePos.x = y;
        mousePos.y = x;
        if(modal.is_active){

            if(modal.is_Clicked(x,y)){
                if(modal.is_Clicked(x,y)==1){
                    win->close_window();
                }
                else{
                    modal.is_active=false;
                    render();

                }
                  
            }
            break;
        }
        if(gameMode.is_Clicked(x,y)){
            win->set_screen(1);
        }else if(puzzleMode.is_Clicked(x,y)){
            win->set_screen(2);

        }else if(exit.is_Clicked(x,y)){
            modal.is_active=true;
            modal.set(1,"Do you want to exit game?");
            render();
        }
        break;
    case SDL_MOUSEBUTTONUP:
        break;

    case SDL_MOUSEMOTION:
        SDL_GetMouseState(&x, &y);
        mousePos.x = y;
        mousePos.y = x;
        break;
        // check if piece is dragging

    default:
        break;
    }  
}