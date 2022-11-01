#pragma once
#include "./GameScreen.hpp"
#include "./Component.cpp"
#include "./Window.hpp"
#include <iostream>
namespace states{
 enum state{idle,wrong,solved};
};
class PuzzleScreen : public GameScreen
{
    int puzzle_solved;
    int hint_taken;
    int correct_move;
    int wrong_move;
    int state;
    std::string fenn; 
    std::string move[100];
    int current_move;
    int total_moves;
    bool hint;
    Box current_position;
    Box next_position;
    //buttons
    Button hintbtn;
    Button tabtn;
    Button nxtbtn;


public:
    PuzzleScreen(Window *win) : GameScreen(win, 0)
    {
        puzzle_solved = 0;
        hint_taken = 0;
        correct_move = 0;
        wrong_move = 0;
        state=states::idle;
        hint = false;
        load_assets();
        load_puzzle();
    }

protected:
    void load_puzzle()
    {
        fenn = "r1b1kb1r/pp2q3/2n3p1/2p1P2p/5Q2/1P2pN2/PBP3PP/2KR1B1R w kq - 0 16";
        move[0] = "f4e3";
        move[1] = "f8h6";
        move[2] = "e3h6";
        move[3] = "h8h6";
        current_move = -1;
        total_moves=4;
        game.init_game(fenn);
        move_bot();
    }
    void move_bot()
    {
        render();
        SDL_Delay(1200);
        parse_move();
        game.piece_selection(current_position.y, current_position.x);
        game.piece_move(next_position.x, next_position.y);
        fenn = game.get_fen();
        hint = false;
        render();
        parse_move();
    }

    void parse_move()
    {
        current_move += 1;
        current_position.y = move[current_move].c_str()[0] - 97;
        current_position.x = 8 - (move[current_move].c_str()[1] - 48);
        next_position.y = move[current_move].c_str()[2] - 97;
        next_position.x = 8 - (move[current_move].c_str()[3] - 48);
    }
     void handle_move(int y, int x, bool dat)
    {
       
         if (current_move % 2 == 0)
        {

            GameScreen::handle_move(y, x, dat);
            
        }
        else
        {
          
            bool chk = (Box(current_position.x, current_position.y) == game.get_currentChessPiece()->get_position()) && (Box(y,x) == Box(next_position.x, next_position.y));
        
            int turn = game.get_turn();
            GameScreen::handle_move(y, x, dat);
            if (turn != game.get_turn())
            {
                if (chk)
                {
                
                    correct_move += 1;
                    hint=false;
                }
                else
                {
                    wrong_move += 1;
                    state=states::wrong;
                }
                if(total_moves==current_move+1 && state!=states::wrong){
                         puzzle_solved += 1;
                    state=states::solved;
                    
                }
             
                if (state==states::idle)
                {
                        std::cout <<current_move<<"\n";
                    move_bot();
                }
            }
          
    }
    }
    void modal_handler()
    {
        int x = mousePos.y;
        int y = mousePos.x;
        modal.is_active = false;
        int id = (modal.is_Clicked(x, y) + 1) / 2;
        if (modal.is_Clicked(x, y) % 2 == 1)
        {
            if (id == 1)
            {
                if(!hint){
                hint_taken+=1;
               hint=true;

                }
             
            }
            else if (id == 2)
            {
                std::cout << "Exit Now\n";
            }
        }
    }
    virtual int button_handler()
    {
        int x = mousePos.y;
        int y = mousePos.x;
        if (hintbtn.is_Clicked(x, y))
        {
                if(state==states::idle && !hint){

            modal.is_active = true;
            modal.set(1, "Do you Want to take hint?");
           
                }else if(state==states::wrong){
                game.init_game(fenn);
                state=states::idle;
                }else if(state==states::solved){
                state=states::idle;
                    load_puzzle();

                }
                 render();
            return 1;
        }
        else if (exitbtn.is_Clicked(x, y))
        {
        
            modal.is_active = true;
            modal.set(2, "Do you Want to Exit?");
            std::cout << "Exit Button Clicked\n";
            render();
            return 1;
        }
        
        return state;
    }
    void load_assets();
    void render_sidebar();
    void show_hint();
 
};
