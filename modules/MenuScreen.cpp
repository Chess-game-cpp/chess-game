#pragma once
#include "MenuScreen.hpp"
#include <SDL2/SDL.h>

MenuScreen::MenuScreen(Window * win){
    modal.is_active=false;
    this->win=win;
    //load background assets;
    bgtexture = TextureManager::load_image_texture("assets/bg.png",win->render);
   
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
   
 
    switch (e.type)
    {
    case SDL_MOUSEBUTTONDOWN:

      
        if(modal.is_active){

            if(modal.is_Clicked(mousePos.x,mousePos.y)){
                if(modal.is_Clicked(mousePos.x,mousePos.y)==1){
                    win->close_window();
                }
                else{
                    modal.is_active=false;
                    render();

                }
                  
            }
            break;
        }
        
        if(gameMode.is_Clicked(mousePos.x,mousePos.y)){
            win->set_screen(3);
        }else if(puzzleMode.is_Clicked(mousePos.x,mousePos.y)){
            win->set_screen(2);

        }else if(exit.is_Clicked(mousePos.x,mousePos.y)){
            modal.is_active=true;
            modal.set(1,"Do you want to exit game?");
            render();
        }
        break;
    case SDL_MOUSEBUTTONUP:
        break;

    case SDL_MOUSEMOTION:

        break;
        // check if piece is dragging

    default:
        break;
    }  
}

GameOptionScreen::GameOptionScreen(Window * win){
    this->win=win;
    //load background assets
    bgtexture = TextureManager::load_image_texture("assets/bg.png",win->render);
    //initialize modal
    modal.init(win->render,0,0,dim::width,dim::height);

    //initialize Button
    goBack.init(win->render,"goback",67,515);
    startGame.init(win->render,"startgame",67+140,515);
    // initialize player box
    
     players.add(new Button(win->render,"playername",64,230,false,true));
     players.add(new Button(win->render,"playername",350,230,false,true));
     limits.set_select(1);
     limits.add(new Button(win->render,"limit1",77,373,false,true));
     limits.add(new Button(win->render,"limit2",77+100,373,false,true));
     limits.add(new Button(win->render,"limit3",77+200,373,false,true));
     limits.add(new Button(win->render,"limit4",77+300,373,false,true));

}
void GameOptionScreen:: render(){
SDL_RenderClear(win->render);
SDL_Rect rect;
rect.x=0;
rect.y=0;
rect.w=dim::width;
rect.h=dim::height;
SDL_RenderCopy(win->render,bgtexture,NULL,&rect);
SDL_Rect rect2={64,199,244,0};
TextureManager::set_font("assets/bebasneue.ttf",30);
TextureManager::render_text("WHITE PLAYER",BLACK,win->render,rect2,0,1);
rect2.x=350;
rect2.w=244;
rect2.y=199;
TextureManager::render_text("BLACK PLAYER",BLACK,win->render,rect2,0,1);
players.render(win->render);
SDL_Rect text_rect={75,234,200,52};
TextureManager::render_text(win->players[0],BLACK,win->render,text_rect,1,0);
SDL_Rect text_rect2={75+290,234,200,52};
TextureManager::render_text(win->players[1],BLACK,win->render,text_rect2,1,0);
rect2.x=65;
rect2.y=334;
TextureManager::render_text("TIME LIMIT",BLACK,win->render,rect2);
limits.render(win->render);
goBack.render(win->render);
startGame.render(win->render);
if(modal.is_active){
    modal.render(win->render);
}
SDL_RenderPresent(win->render);


}
void GameOptionScreen::event_handle(SDL_Event & e){
 
    switch (e.type)
    {
    case SDL_KEYDOWN:
    //    std::cout<<e.key.type<<std::endl;
        if(players.get_selected()){
        int len=win->players[players.get_selected()-1].length();
        if((e.key.keysym.sym>96 && e.key.keysym.sym<=122) || (e.key.keysym.sym>47 && e.key.keysym.sym<=57)){
         
            if(len<12){
            win->players[players.get_selected()-1]+=char(e.key.keysym.sym);

            }
        }else if(e.key.keysym.sym==8){
            if(len>1){
            win->players[players.get_selected()-1].erase(len-1,len);
            }else{
            win->players[players.get_selected()-1]=" ";
                
            }
            }
      
        }
        render();
        SDL_Delay(50);
        break;
       
    
    case SDL_MOUSEBUTTONDOWN:

        if(modal.is_active){

            if(modal.is_Clicked(mousePos.x,mousePos.y)){
                if(modal.is_Clicked(mousePos.x,mousePos.y)%2==0){
                    modal.is_active=false;
                    render();
                }
                else{
                    if(modal.is_Clicked(mousePos.x,mousePos.y)==1){
                        win->set_screen(0);

                    }else if (modal.is_Clicked(mousePos.x,mousePos.y)==3){
                        switch(limits.get_selected()){
                            case 1:
                            win->timer=0;
                            break;
                            case 2:
                            win->timer=60000;
                            break;
                            case 3:
                            win->timer=600000;
                            break;
                            case 4:
                            win->timer=1800000;
                            break;

                            default:
                            break;

                        }
                        if(win->players[0]==" "){
                            win->players[0]="WHITE";
                        }
                        if(win->players[1]==" "){
                           win->players[1]="BLACK";
                        }
                        win->set_screen(1);
                    }
               

                }
                  
            }
            break;
        }
        players.update_selection(mousePos.x,mousePos.y);

        
        limits.update_selection(mousePos.x,mousePos.y);
        if(goBack.is_Clicked(mousePos.x,mousePos.y)){
            modal.is_active=true;
            modal.set(1,"Do you want to go back to menu?");
        
        }else if(startGame.is_Clicked(mousePos.x,mousePos.y)){
            modal.is_active=true;
            modal.set(2,"Do you want to start game?");
            

        }
        render();
        break;
    case SDL_MOUSEBUTTONUP:
        break;

    case SDL_MOUSEMOTION:
     
        break;
        // check if piece is dragging

    default:
        break;
    }  
}