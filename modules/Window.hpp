#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "./GameScreen.hpp"
#include "./GameScreen.hpp"
using namespace std;
class Window
{
    std::string title;
    int closed = false;
    SDL_Event ev;

public:
    int width = 800;
    int height = 600;
    int size,offsetX,offsetY;
    SDL_Window *window = nullptr;
    Screen * screen=nullptr;
    bool isClosed() const { return closed; }
    SDL_Surface *surface = nullptr;
    SDL_Renderer *render = NULL;
    GameScreen g;

    SDL_Texture *texture = NULL;
    Window(const std::string &title, int width, int height)
    {
        
      
        this->title = title;
        this->width = width;
        this->height = height;
        if (!init())
        {
            closed = true;
        }
        render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        g.set_window(this);
        screen= &g;
    
    
        while (1)
        {
            if (SDL_PollEvent(&ev) != 0)
            {
                if (ev.type == SDL_QUIT)
                {
                    break;
                }
                handle_event(ev);
            }
        }
    }
    
    void handle_event(SDL_Event &e)
    {

        if (e.type == SDL_WINDOWEVENT)
        {
            //window event
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
            width=e.window.data1;
            height=e.window.data2;
            screen->render();
      
            SDL_RenderPresent(render);
               
                break;
       
            break;

            default:
                break;
            }
            
        }
            screen->event_handle(e);
    }
    bool init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "Failed";
            return 0;
        }
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
     

        if (window == nullptr)
        {
            std::cout << "Failed to create Window.\n";
            return 0;
        }
        //      if(!(IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG){
        //     std::cout <<"GAI";
        // }
        return 1;
    }
    // SDL_Surface * loadPng(std::string path ){
    //     SDL_Surface image=IMG_Load(path);
    //     return image;

    // }
    ~Window()
    {
        SDL_DestroyWindow(window);

        SDL_Quit();
    }

    
};
