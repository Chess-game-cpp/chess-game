namespace dim
{
  const int height = 672;
  const int width = 950;
  const int size = height / 8;
  const int sidebar = width - height;
  const int modal_h = 134;
  const int modal_w = 332;
  const int modal_mv = 20;
  const int modal_mh = 20;

};
Mix_Chunk *sounds[10];

#pragma once
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "TextureManager.cpp"
#include "./Component.cpp"
#define TIMER 100
using namespace std;

// declaring classes
class Screen;
class GameScreen;
class PuzzleScreen;
class MenuScreen;
class Window;
class Board;
class ChessPiece;
// Box class to represent square
class Box
{
public:
  int x; // xpos
  int y; // y pos
  Box()
  {
    x = -1;
    y = -1;
  }
  Box(int x, int y)
  {
    this->x = x;
    this->y = y;
  }
  // check if two Box objects have same value
  bool operator==(Box a)
  {
    if ((this->x == a.x) && (this->y == a.y))
    {
      return 1;
    }
    return 0;
  }

  void display()
  {
    // display value og box
    std::cout << x << "," << y << std::endl;
  }
  bool is_valid()
  {
    // box is valid
    if (x < 0 || y < 0)
    {
      return 0;
    }
    return 1;
  }
  void setNull()
  {
  }
};
// namespace containing dimensions window components

// global varaiables declaration
Box mousePos;
Modal modal;

// functions
void load_sounds()
{
  // start-1
  // move-2
  // capture-3
  // castling-4
  // check - 5
  // gameover-6
  for (int i = 0; i < 7; i++)
  {
    sounds[i] = Mix_LoadWAV(("assets/sounds/" + to_string(i + 1) + ".wav").c_str());
  }
}
void free_sounds()
{
  for (int i = 0; i < 10; i++)
  {
    Mix_FreeChunk(sounds[i]);
  }
}
