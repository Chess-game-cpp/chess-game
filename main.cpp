#include <iostream>
#include <SDL2/SDL.h>
 #include <SDL2/SDL_image.h>
using namespace std;


class Window
{
    std::string title;
    int width = 800;
    int height = 600;
    int closed = false;
    int size,offsetX,offsetY;
    SDL_Event ev;

public:
    SDL_Window *window = nullptr;
    bool isClosed() const { return closed; }
    SDL_Surface *surface = nullptr;
    SDL_Renderer *render = NULL;

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
        create_chess_board();
        SDL_RenderPresent(render);
    
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
            create_chess_board();
            SDL_RenderPresent(render);
               
                break;
       
            break;

            default:
                break;
            }
        }
    }
    void create_chess_board()
    {
                size=width>height?height:width;
        offsetX=width>height?(width-height)/2:0 ;
        offsetY=width<height?(height-width)/2:0 ;
        SDL_RenderClear(render);
           SDL_RenderPresent(render);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                create_rectangle(i, j, render);
            }
        }
         SDL_Surface * image=IMG_Load("assets/pieces.png");
         SDL_Texture *texture=SDL_CreateTextureFromSurface(render,image);
         SDL_Rect rect,rect2;
         for(int i=0;i<6;i++){


         rect.x=80*i;
         rect.y=0;
         rect.w=80;
         rect.h=80;
         rect2.x=offsetX+(i*(size/8));
         rect2.y=offsetY;
         rect2.w=size/8;
         rect2.h=size/8;
        SDL_RenderCopy(render,texture,&rect,&rect2);
         }

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
             if(!(IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG){
            std::cout <<"GAI";
        }
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

    void create_rectangle(int x, int y, SDL_Renderer *&r)
    {

        SDL_Rect rect;

        rect.x = x * (size / 8)+offsetX;
        rect.y = y * (size / 8)+offsetY;
        rect.w = (size / 8);
        rect.h = (size / 8);
        if ((x + y) % 2 == 1)
        {
            // even =black
            SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
            // odd = white
        }
        // SDL_SetRenderDrawColor(r, 0, 255, 255,255);
        SDL_RenderFillRect(r, &rect); // create_rect
    }
};
 
int main(int argv, char **args)
{
    
    Window w("Hello", 650, 650);

    return 0;
}