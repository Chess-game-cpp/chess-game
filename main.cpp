//declaring classes
class Screen;
class GameScreen;
class Window;
class Board;
class ChessPiece;
class Box;
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define TIMER 100
#include "modules/Window.hpp"
#include "modules/GameScreen.cpp"

using namespace std;


int main(int argv, char **args)
{
    //initailizing the window object
    Window w("Chess Game", 950, 670);

    return 0;
}
