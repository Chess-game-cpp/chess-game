#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "modules/global.cpp"
#include "modules/Window.hpp"
#include "modules/Board.cpp"
#include "modules/GameScreen.cpp"
#include "modules/PuzzleScreen.cpp"
#include "modules/MenuScreen.cpp"

using namespace std;

int main(int argv, char **args)
{
    // initailizing the window object
    load_sounds();
    Window w("Chess Game", dim::width, dim::height);
    TextureManager::free();
    TextureManager::free_font();
    free_sounds();
    return 0;
}
