#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "./Screen.hpp"
#include "./Timer.hpp"
#include "./Board.hpp"
#include "./Component.cpp"
using namespace std;
// GameScreen class inherited from abstract class Screen
class GameScreen : public Screen
{

    Timer timer;
    SDL_Texture *timer_texture;
    Button exitbtn;
    Button resbtn;

protected:
    Board game; // object game
    SDL_Texture *texture;
    SDL_Texture *btexture;
    bool rendering;
    bool dragging;
    Box mousePos;
    Modal modal;
    bool modal_active;

public:
    // functions declartaions

    GameScreen(Window *, int = 0);
    void render();
    void event_handle(SDL_Event &);
    ~GameScreen()
    {
        SDL_DestroyTexture(texture);

        if (timer.is_active())
        {
            SDL_RemoveTimer(timer.get_id());
        }
    }

private:
    static Uint32 timer_update(Uint32 interval, void *data)
    {
        int s = SDL_GetTicks64();
        GameScreen *gmscrn = (reinterpret_cast<GameScreen *>(data));
        int time = gmscrn->timer.adjust_time(gmscrn->game.get_turn());
        if (time == 1)
        {
            gmscrn->render();
        }
        else if (time == 2)
        {
            gmscrn->game.times_up();
            gmscrn->render();

            return 0;
        }

        return TIMER - (SDL_GetTicks64() - s);
    }
    std::string mstotime(int);

protected:
    void load_assets();
    void create_chess_board();
    void create_rectangle(int, int, SDL_Renderer *&, int);
    void render_chesspiece(int, int, int, int, int = dim::size);
    void load_other();
    void render_chessgame();
    void render_sidebar();
    void modal_handler()
    {
        int x = mousePos.y;
        int y = mousePos.x;
        modal_active = false;
        int id = (modal.is_Clicked(x, y) + 1) / 2;
        if (modal.is_Clicked(x, y) % 2 == 1)
        {
            if (id == 1)
            {
                std::cout << "Restart Now\n";
            }
            else if (id == 2)
            {
                std::cout << "Exit Now\n";
            }
        }
    }
    int button_handler()
    {
        int x = mousePos.y;
        int y = mousePos.x;
        if (resbtn.is_Clicked(x, y))
        {
            modal_active = true;
            modal.set(1, "Do you Want to Restart?");
            std::cout << "Restart Button Clicked\n";
            render();
            return 1;
        }
        else if (exitbtn.is_Clicked(x, y))
        {
            modal_active = true;
            modal.set(2, "Do you Want to Exit?");
            std::cout << "Exit Button Clicked\n";
            render();
            return 1;
        }
        return 0;
    }
};
