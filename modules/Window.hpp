#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "./GameScreen.hpp"

using namespace std;
// class to render SDL window
class Window
{
    std::string title; // title
    int closed = false;
    SDL_Event ev;

public:
    int width;
    int height;
    int size, offsetX, offsetY;
    SDL_Window *window = nullptr;
    Screen *screen = nullptr;
    bool isClosed() const { return closed; }
    SDL_Surface *surface = nullptr;
    SDL_Renderer *render = NULL;
    // GameScreen g;
    SDL_Texture *texture = NULL;
    // window constructor
    Window(const std::string &title, int width, int height)
    {

        this->title = title;
        this->width = width;
        this->height = height;
        // check if window failed to initialize
        if (!init())
        {
            closed = true;
            return; 
        }
        // create renderer for window
        render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        // set window pointer in gameScreen to current
        // set current screen as gameScreen g
        screen = new GameScreen(this,10000);
        // gameloop
        while (!closed)
        {
            // poll event
            if (SDL_PollEvent(&ev) != 0)
            {
                // close button clicked
                if (ev.type == SDL_QUIT)
                {
                    break;
                }
                // handle events
                handle_event(ev);
            }
        }
    }

    void handle_event(SDL_Event &e)
    {

        if (e.type == SDL_WINDOWEVENT)
        {
            // window event
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_RESIZED:
                // resize event handler
                width = e.window.data1;
                height = e.window.data2;
                screen->render();
                SDL_RenderPresent(render);
                break;
            default:
                break;
            }
        }
        // screen event handling
        screen->event_handle(e);
    }
    bool init()
    {
        // initialize SDL window
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "Failed";
            return 0;
        }
        // create window
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);

        //initialize ttf
     if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                   
    }
        // check if window is null
        if (window == nullptr)
        {
            std::cout << "Failed to create Window.\n";
            return 0;
        }
        return 1;
    }

    ~Window()
    {
        // destroy the window
        delete screen;
        SDL_FreeSurface(surface);
        SDL_DestroyRenderer(render);
        SDL_DestroyTexture(texture);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};
