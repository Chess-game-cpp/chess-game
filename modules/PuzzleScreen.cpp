#pragma once
#include "./Window.hpp"
#include "PuzzleScreen.hpp"
#include <iostream>
void PuzzleScreen::render_sidebar()
{
   // render background
   SDL_Rect rec2;
   rec2.x = 0;
   rec2.y = 0;
   rec2.h = dim::height;
   rec2.w = dim::sidebar;

   SDL_Rect rec3;
   rec3.x = dim::height;
   rec3.y = 0;
   rec3.h = dim::height;
   rec3.w = dim::sidebar;

   SDL_RenderCopy(win->render, btexture, &rec2, &rec3);
   // title mode
 
   TextureManager::set_font("assets/bebasneue.ttf", 25);
   rec3.h = 0;
   rec3.y = 50;
   TextureManager::render_text("Puzzle Mode", BLACK, win->render, rec3, 0, 1);
   TextureManager::set_font("assets/bebasneue.ttf", 22);
   rec3.y += 40;
   TextureManager::render_text("Puzzle Solved: " + to_string(puzzle_solved), BLACK, win->render, rec3, 0, 1);
   rec3.y += 25;
   TextureManager::render_text("Correct Moves: " + to_string(correct_move), BLACK, win->render, rec3, 0, 1);
   rec3.y += 25;
   TextureManager::render_text("Wrong Moves: " + to_string(wrong_move), BLACK, win->render, rec3, 0, 1);
   rec3.y += 25;
   TextureManager::render_text("Hints Taken: " + to_string(hint_taken), BLACK, win->render, rec3, 0, 1);
   // btns
   exitbtn.render(win->render);
   rec2 = rec3;
   rec3.y = 300;
   rec2.y = 334;
      TextureManager::set_font("assets/bebasneue.ttf", 30);
   if (state == states::solved)
   {
      TextureManager::render_text("Puzzle Solved!!!", GREEN, win->render, rec2, 0, 1);

      nxtbtn.render(win->render);
   }
   else if (state == states::wrong)
   {
      if (hint)
      {
         TextureManager::render_text("USE HINT!!", BLUE, win->render, rec3, 0, 1);
      }
      TextureManager::render_text("INCORRECT MOVE!!", RED, win->render, rec2, 0, 1);

      tabtn.render(win->render);
   }
   else
   {
      if (hint)
      {
         TextureManager::render_text("USE HINT!!", BLUE, win->render, rec3, 0, 1);
      }
      hintbtn.render(win->render);
   }
}
void PuzzleScreen::load_assets()
{
   //  std::cout << "ol";

   exitbtn.init(win->render, "exit", dim::height + (dim::sidebar - 139) / 2, dim::height - 65);
   tabtn.init(win->render, "tryagain", dim::height + (dim::sidebar - 139) / 2, dim::height - 120);
   nxtbtn.init(win->render, "next", dim::height + (dim::sidebar - 139) / 2, dim::height - 120);
   hintbtn.init(win->render, "hint", dim::height + (dim::sidebar - 139) / 2, dim::height - 120);
   fstream file("assets/puzzle.csv");
   std::string line;
   while (std::getline(file,line))
   {
   Puzzles.push_back(line);
 
   }
   file.close();
}
void PuzzleScreen::show_hint()
{
   if (hint)
   {
      create_rectangle(current_position.y, current_position.x, win->render, 7);
   }
}
bool PuzzleScreen::modal_handler()
    {
        int x = mousePos.x;
        int y = mousePos.y;
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
                
                win->set_screen(0);
                return 0;
            }
        }
        return 1;
    }