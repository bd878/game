#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

const int FPS = 5;
const int DELAY_TIME = 1000.0f / FPS;

int main() {
  std::cout << "init game...\n" << std::endl;

  Uint32 frameStart, frameTime;

  if (TheGame::Instance()->Init("Test game",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT, false)
  ) {
    while (TheGame::Instance()->Running()) {
      frameStart = SDL_GetTicks();

      TheGame::Instance()->HandleEvents();
      TheGame::Instance()->Update();
      TheGame::Instance()->Render();

      frameTime = SDL_GetTicks() - frameStart;

      if (frameTime < DELAY_TIME)
      {
        SDL_Delay((int)(DELAY_TIME - frameTime));
      }
    }
  } else {
    std::cout << "game init failed\n" << std::endl;
  }

  TheGame::Instance()->Clean();
  return 0;
}