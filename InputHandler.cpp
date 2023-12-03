#include <SDL2/SDL.h>
#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::Instance() {
  if (_instance == nullptr) {
    _instance = new InputHandler;
  }
  return _instance;
}

void InputHandler::HandleEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        TheGame::Instance()->Quit();
        break;
    }
  }
}