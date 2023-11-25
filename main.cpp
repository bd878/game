#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

int main() {
  std::cout << "init game...\n" << std::endl;

  if (Game::Instance()->Init("Test game",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT, false)
  ) {
    while (Game::Instance()->Running()) {
      SDL_Delay(1000*10);
    }
  } else {
    std::cout << "game init failed\n" << std::endl;
  }

  Game::Instance()->Clean();
  return 0;
}