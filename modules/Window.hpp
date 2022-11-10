#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "./GameScreen.hpp"
#include "./PuzzleScreen.hpp"
#include "./MenuScreen.hpp"
using namespace std;

// class to render SDL window
class Window
{

    std::string title; // title
    int closed = false;
    SDL_Event ev;
    SDL_Window *window = nullptr;
    Screen *screen = nullptr;
    SDL_Surface *surface;

public:
    std::string players[2];
    int width;
    int height;
    int timer;
    bool isClosed() const { return closed; }
    void close_window()
    {
        closed = true;
    }
    SDL_Renderer *render;

    // window constructor
    Window(const std::string &title, int width, int height)
    {
        timer = 0;
        players[0] = " ";
        players[1] = " ";
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
        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
        // set window pointer in gameScreen to current
        // set current screen as gameScreen g
        set_screen(0);
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
                if (ev.type == SDL_MOUSEBUTTONDOWN || ev.type == SDL_MOUSEBUTTONUP || ev.type == SDL_MOUSEMOTION)
                {
                    int x,y;
                    SDL_GetMouseState(&x, &y);
                    mousePos.x = x;
                    mousePos.y = y;
                }
                // handle events
                handle_event(ev);
            }
        }
    }
    void set_screen(int sc)
    {
        delete screen;
        if (sc == 0)
        {
            screen = new MenuScreen(this);
        }
        else if (sc == 1)
        {
            screen = new GameScreen(this, timer);
        }
        else if (sc == 2)
        {
            screen = new PuzzleScreen(this);
        }
        else if (sc == 3)
        {

            screen = new GameOptionScreen(this);
        }
        screen->render();
    };

    ~Window()
    {
        // destroy the window
        delete screen;
        SDL_FreeSurface(surface);
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

private:
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
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        {
            std::cout << "Failed";
            return 0;
        }
        // create window
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

        // initialize ttf
        if (TTF_Init() == -1)
        {
            printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        }
        // Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        }
        load_sounds();

        // check if window is null
        if (window == nullptr)
        {
            std::cout << "Failed to create Window.\n";
            return 0;
        }
        return 1;
    }
};
