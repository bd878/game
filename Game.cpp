#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

Game* Game::_instance = nullptr;

Game* Game::Instance() {
  if (_instance == nullptr) {
    _instance = new Game;
  }
  return _instance;
}

bool Game::Init(const std::string& title, int x, int y, int w, int h, int flags) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "SDL2 could not be initializer"
      << SDL_GetError() << std::endl;
    is_inited = false;
    return is_inited;
  }

  _window = SDL_CreateWindow(title.c_str(),
    x, y, w, h, flags);

  if (_window == NULL) {
    std::cerr << "Window could not be created"
      << SDL_GetError() << std::endl;
    is_inited = false;
    return is_inited;
  }

  _renderer = SDL_CreateRenderer(_window, -1, 0);
  if (_renderer == NULL) {
    std::cerr << "Renderer could not be created"
      << SDL_GetError() << std::endl;
    is_inited = false;
    return is_inited;
  }

  if (SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255) < 0) {
    std::cerr << "Could set renderer color"
      << SDL_GetError() << std::endl;
    is_inited = false;
    return is_inited;
  }

  const SDL_Rect rect = {0, 0, 30, 30};
  if (SDL_RenderFillRect(_renderer, &rect) < 0) {
    std::cerr << "Could not fill rect"
      << SDL_GetError() << std::endl;
    is_inited = false;
    return is_inited;
  }

  is_inited = true;
  is_running = true;
  return is_inited;
}

bool Game::Running() {
  return is_running;
}

void Game::Clean() {}