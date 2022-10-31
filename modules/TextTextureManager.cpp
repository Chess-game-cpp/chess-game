#pragma once
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <iostream>
namespace TextureManager
{
    TTF_Font *font = NULL;
    int width = 0;
    int height = 0;
    SDL_Texture *texture = NULL;

    void free()
    {
        SDL_DestroyTexture(texture);
    }
    void free_font()
    {
        TTF_CloseFont(font);
    }
    void set_font(std::string font_name, int font_size)
    {
        free_font();

        font = TTF_OpenFont(font_name.c_str(), font_size);
    }

    void render_text(std::string s, SDL_Color &color, SDL_Renderer *&render, SDL_Rect &rect, int v_align = 0, int h_align = 0)
    {
        SDL_Surface *text = TTF_RenderText_Solid(font, s.c_str(), color);
        height = text->h;
        width = text->w;
        free();
        texture = SDL_CreateTextureFromSurface(render, text);
        if (v_align == 0)
        {
            // rect.y=;
            // start
        }
        else if (v_align == 1)
        {
            rect.y += (rect.h / 2) - (height / 2);
            // middle
        }
        else if (v_align == 2)
        {
            rect.y += rect.h - height;
            // end
        }
        if (h_align == 0)
        {
        }
        else if (h_align == 1)
        {
            rect.x += (rect.w / 2) - (width / 2);
        }
        else if (h_align == 2)
        {
            rect.x += rect.w - width;
        }

        rect.w = width;
        rect.h = height;
        SDL_RenderCopy(render, texture, NULL, &rect);
    }
};