#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

class Window
{
    int screen_height;
    int screen_width;

public:
    bool init(int h, int w);
    Window(int h, int w)
    {
        init(h,w);
    }


    ~Window()
    {
        // Destroy window
        // SDL_DestroyWindow(window);

        // Quit SDL subsystems
        SDL_Quit();
    }
};

bool Window::init(int h, int w)
{
    screen_height = h;
    screen_width = w;
    // The window we'll be rendering to
    SDL_Window *window = NULL;

    // The surface contained by the window
    SDL_Surface *screenSurface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    else
    {
        // Create window
        window = SDL_CreateWindow("Chess_Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_height, screen_width, SDL_WINDOW_RESIZABLE);

        // Renderer
        SDL_Renderer *ren = NULL;
        ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }

        else
        {
            SDL_Event e;
            bool quit = false;
            while (quit == false)
            {
                // Get window surface
                screenSurface = SDL_GetWindowSurface(window);
                screen_height = screenSurface->h;
                screen_width = screenSurface->w;

                // Fill the surface white
                // SDL_FillRect(screenSurface, NULL, SDL_MapRGB
                //(screenSurface->format, 0xFF, 0xFF, 0xFF));
                SDL_Rect rec;
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        rec.x = (screen_width / 8) * i;
                        rec.y = (screen_height / 8) * j;
                        rec.h = screen_height / 8;
                        rec.w = screen_width / 8;

                        if ((i + j) % 2 == 0)
                        {
                            // even = white

                            SDL_FillRect(screenSurface, &rec, SDL_MapRGB(screenSurface->format, 255, 255, 255));
                        }
                        else
                        {
                            SDL_FillRect(screenSurface, &rec, SDL_MapRGB(screenSurface->format, 0, 0, 0));
                        }
                    }
                }

                // Update the surface
                SDL_UpdateWindowSurface(window);
                // To keep the window stay
                SDL_PollEvent(&e);
                if (e.type == SDL_QUIT)
                    quit = true;
            }
        }
    }

}

using namespace std;


int main(int argc, char *args[])
{
    // cout << "Hello world";
    Window w(650, 650);
}