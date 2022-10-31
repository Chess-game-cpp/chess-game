// declaring classes
class Screen;
class GameScreen;
class Window;
namespace dim
{
    const int height = 672;
    const int width = 950;
    const int size = height / 8;
    const int sidebar = width - height;
};
class Board;
class ChessPiece;
class Box;
#define TIMER 100
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "modules/TextTextureManager.cpp"
#include "modules/Window.hpp"
#include "modules/Board.cpp"
#include "modules/GameScreen.cpp"

using namespace std;

int main(int argv, char **args)
{
    // initailizing the window object
    Window w("Chess Game", dim::width, dim::height);
    TextureManager::free();
    TextureManager::free_font();
    return 0;
}
