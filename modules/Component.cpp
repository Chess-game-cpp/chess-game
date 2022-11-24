#pragma once
#include <SDL2/SDL.h>
#include <iostream>

class Button
{
    SDL_Rect button_rect;
    bool hover;
    bool select;
    SDL_Texture *button_texture[3];
    Mix_Chunk * sound;    

public:
    bool is_selected;
    bool free;
    Button()
    {
        sound=NULL;
        free=true;
        is_selected = false;
        for (int i = 0; i < 3; i++)
        {
            button_texture[i] = NULL;
        }
    }
    Button(SDL_Renderer *render, std::string b_text, int bx, int by, bool hover = false, bool select = false,int sound=0)
    {
    
        is_selected = false;
        for (int i = 0; i < 3; i++)
        {
            button_texture[i] = NULL;
        }
        init(render,b_text,bx,by,hover,select,sound);
    }
    void init(SDL_Renderer *render, std::string b_text, int bx, int by, bool hover = false, bool select = false,int sound=5)
    {
        // if(sound!=0){
            // this->sound=sounds[sound-1];
        // }
        this->hover = hover;
        this->select = select;
        if (button_texture[0] == NULL)
        {

            button_texture[0] = TextureManager::load_image_texture("assets/buttons/" + b_text + ".png", render, &button_rect);
            if (hover)
            {
                button_texture[1] = TextureManager::load_image_texture("assets/buttons/" + b_text + "_hover.png", render);
            }
            if (select)
            {
                button_texture[2] = TextureManager::load_image_texture("assets/buttons/" + b_text + "_selected.png", render);
            }
        }
        button_rect.x = bx;
        button_rect.y = by;
    }
    ~Button()
    {
       if(free){

        for (int i = 0; i < 3; i++)
        {
            SDL_DestroyTexture(button_texture[i]);
        }
       }
    }

    bool is_Clicked(int x, int y)
    {
        bool value=((x > button_rect.x && x < (button_rect.x + button_rect.w)) && (y > button_rect.y && y < (button_rect.y + button_rect.h)));
        // if(value && this->sound!=NULL){
        //       Mix_PlayChannel( -1, this->sound, 0 );
        // }
        return value ;
    }

    void render(SDL_Renderer *&render)
    {
        if(is_selected && select){

        SDL_RenderCopy(render, button_texture[2], NULL, &button_rect);
        }else{

        SDL_RenderCopy(render, button_texture[0], NULL, &button_rect);
        }
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
    bool is_active;
    Modal()
    {
        is_active = false;
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
        yesbtn.init(render, "yes", (rect.x + dim::modal_mv), (rect.y + rect.h - dim::modal_mh) - 36);
        cancelbtn.init(render, "cancel", (rect.x + rect.w - dim::modal_mv - 81), (rect.y + rect.h - dim::modal_mh) - 36);
    }
    void set(int id, std::string ask)
    {
        this->ask = ask;
        this->id = id;
    }
    void render(SDL_Renderer *render)
    {
        SDL_Rect txrect = rect;
        // txrect.x += dim::modal_mv;
        txrect.y += dim::modal_mh;
        SDL_SetRenderDrawColor(render, 0, 0, 0, 100);
        SDL_RenderFillRect(render, &rect2);
        SDL_SetRenderDrawColor(render, 240, 240, 240, 230);
        SDL_RenderFillRect(render, &rect);
        TextureManager::set_font("assets/BebasNeue.ttf", 25);
        TextureManager::render_text(ask, BLACK, render, txrect, 0, 1);
        yesbtn.render(render);
        cancelbtn.render(render);
    }
    int is_Clicked(int x, int y)
    {
        if (yesbtn.is_Clicked(x, y))
        {
            return (id * 2) - 1;
        }
        if (cancelbtn.is_Clicked(x, y))
        {
            return (id * 2);
        }
        return 0;
    }
};
template <int size = 10>
class ButtonGroup
{
    Button btn[size];
    int count;
    bool select_one;

public:
    ButtonGroup(bool select = false)
    {
        count = 0;
        select_one = select;
    }
    void set_select(bool i){
        select_one=i;

    }
    
  
    void add(Button * btn)
    {
        if(select_one && count==0){
            btn->is_selected=true;
        }
        btn->free=false;
        this->btn[count]=*btn;
        delete btn;
        count += 1;
    }
    void render(SDL_Renderer *&renderer){
        for (int i = 0; i < count; i++)
        {
            
            btn[i].render(renderer) ;   
        } 
    }
    int update_selection(int x, int y)
    {
        int selected = 0;
        int last = 0;
        for (int i = 0; i < count; i++)
        {
            if (btn[i].is_selected)
            {
                last = i + 1;
            }
            if (btn[i].is_Clicked(x,y))
            {
                selected = i + 1;
                btn[i].is_selected = true;
            }
            else
            {
                btn[i].is_selected = false;
            }
        }
        if (select_one && last != 0 && selected == 0)
        {
            btn[last - 1].is_selected = true;
        }

        return selected;
    }

    int get_selected()
    {
        for (int i = 0; i < count; i++)
        {
            if (btn[i].is_selected)
            {
                return i + 1;
            }
        }
        return 0;
    }
};