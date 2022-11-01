#include <SDL2/SDL.h>
#include <iostream>
class Button
{
    SDL_Texture *button_texture;
    SDL_Rect button_rect;

public:
    Button()
    {
        button_texture = NULL;
    }
    void init(SDL_Renderer *render, std::string b_text, int bx, int by)
    {
        if (button_texture == NULL)
        {

            SDL_Surface *image = IMG_Load(b_text.c_str());
            button_rect.w = image->w;
            button_rect.h = image->h;
            button_texture = SDL_CreateTextureFromSurface(render, image);
            SDL_FreeSurface(image);
        }
        button_rect.x = bx;
        button_rect.y = by;
    }
    ~Button()
    {
        SDL_DestroyTexture(button_texture);
    }

    bool is_Clicked(int x, int y)
    {
        return ((x > button_rect.x && x < (button_rect.x + button_rect.w)) && (y > button_rect.y && y < (button_rect.y + button_rect.h)));
    }

    void render(SDL_Renderer *render)
    {
        SDL_RenderCopy(render, button_texture, NULL, &button_rect);
    }
};
class Modal
{
    int id;
    std::string ask;
    SDL_Rect rect, rect2;
    Button yesbtn;
    Button cancelbtn;

public:
    Modal()
    {
    }
    void init(SDL_Renderer *render, int x, int y, int w, int h)
    {
        rect2.h = h;
        rect2.w = w;
        rect2.x = x;
        rect2.y = y;
        rect.x = x + (w / 2) - (dim::modal_w / 2);
        rect.y = y + (h / 2) - (dim::modal_h / 2);
        rect.w = dim::modal_w;
        rect.h = dim::modal_h;
        yesbtn.init(render, "assets/yes.png", (rect.x + dim::modal_mv), (rect.y + rect.h - dim::modal_mh)-36);
        cancelbtn.init(render, "assets/cancel.png", (rect.x + rect.w - dim::modal_mv-81), (rect.y + rect.h - dim::modal_mh)-36);
    }
    void set(int id, std::string ask)
    {
        this->ask = ask;
        this->id = id;
    }
    void render(SDL_Renderer *render)
    {
        SDL_Color BLACK = {0, 0, 0, 255};
        SDL_Rect txrect = rect;
        // txrect.x += dim::modal_mv;
        txrect.y += dim::modal_mh;
        SDL_SetRenderDrawColor(render, 0, 0, 0, 100);
        SDL_RenderFillRect(render, &rect2);
        SDL_SetRenderDrawColor(render, 240, 240, 240, 230);
        SDL_RenderFillRect(render, &rect);
       TextureManager::set_font("assets/BebasNeue.ttf", 25);
        TextureManager::render_text(ask, BLACK, render, txrect,0,1);
        yesbtn.render(render);
        cancelbtn.render(render);
    }
    int is_Clicked(int x,int y){
        if(yesbtn.is_Clicked(x,y)){
            return (id*2)-1;
        }
        if(cancelbtn.is_Clicked(x,y)){
            return (id*2);

        }
        return 0;
    }
};