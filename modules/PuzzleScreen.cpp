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
   SDL_Color BLACK = {0, 0, 0, 255};
   SDL_Color GREEN = {0, 255, 0, 255};
   SDL_Color BLUE = {0,0, 255, 255};
   SDL_Color RED = {255, 0, 0, 255};
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

   exitbtn.init(win->render, "assets/exit.png", dim::height + (dim::sidebar - 139) / 2, dim::height - 65);
   tabtn.init(win->render, "assets/tryagain.png", dim::height + (dim::sidebar - 139) / 2, dim::height - 120);
   nxtbtn.init(win->render, "assets/next.png", dim::height + (dim::sidebar - 139) / 2, dim::height - 120);
   hintbtn.init(win->render, "assets/hint.png", dim::height + (dim::sidebar - 139) / 2, dim::height - 120);
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
