#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "./Screen.hpp"
#include "./Timer.hpp"
#include "./Board.hpp"
using namespace std;
// GameScreen class inherited from abstract class Screen
class GameScreen : public Screen
{

    Timer timer;

protected:
    Board game; // object game
    SDL_Texture *texture;
    bool rendering;
    bool dragging;
    Box mousePos;
    int mheight;
    int mwidth;
    TTF_Font *font;

public:
    // functions declartaions

    GameScreen(Window *, int = 0);
    void load_assets();
    void render();
    void event_handle(SDL_Event &);

    void create_chess_board();
    void create_rectangle(int, int, SDL_Renderer *&, int);
    void render_chesspiece(int, int, int, int);
    ~GameScreen()
    {
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
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
};
