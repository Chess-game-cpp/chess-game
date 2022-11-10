#pragma once
#include "./GameScreen.hpp"
#include "./Component.cpp"
#include "./Window.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
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
    int current_move;
    bool hint;
    Box current_position;
    Box next_position;
    vector <std::string> Puzzles;
    vector <std::string> moves;
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
        int index=(SDL_GetTicks64()%Puzzles.size());
        stringstream ptxt(Puzzles[index]+" ");
        Puzzles.erase(Puzzles.begin()+index);
        std::getline(ptxt,fenn,',');
        std::string line;
        moves.clear();
        while (std::getline(ptxt,line,' '))
        {
            moves.push_back(line);

            /* code */
        }
        
        // fenn = "r1b1kb1r/pp2q3/2n3p1/2p1P2p/5Q2/1P2pN2/PBP3PP/2KR1B1R w kq - 0 16";

        // move[0] = "f4e3";
        // move[1] = "f8h6";
        // move[2] = "e3h6";
        // move[3] = "h8h6";
        current_move = -1;
        game.init_game(fenn);
        move_bot();
    }

    void move_bot()
    {
        render();
        SDL_Delay(1200);
        parse_move();
        game.piece_selection(current_position.y, current_position.x);
        GameScreen::handle_move(next_position.x,next_position.y);
        if(game.get_gameState()==3){
            game.promote_pawn(5);
        }
        fenn = game.get_fen();
        hint = false;
        render();
        parse_move();
    }

    void parse_move()
    {
        current_move += 1;
        current_position.y = moves[current_move].c_str()[0] - 97;
        current_position.x = 8 - (moves[current_move].c_str()[1] - 48);
        next_position.y = moves[current_move].c_str()[2] - 97;
        next_position.x = 8 - (moves[current_move].c_str()[3] - 48);
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
            if(game.get_gameState()==3){
          game.promote_pawn(5);
          }
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
    
                if(moves.size()==current_move+1 && state!=states::wrong){
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
    bool modal_handler();
    virtual int button_handler()
    {
        int x = mousePos.x;
        int y = mousePos.y;
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
