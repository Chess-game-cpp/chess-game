#pragma once
//abstract class for the screens
 class Screen 
{

    public:
    virtual void render()=0;
    virtual void event_handle(SDL_Event &) = 0;
    Window *win;
  
    virtual ~Screen(){

    }

};