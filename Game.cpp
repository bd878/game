#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"
#include "Square.h"

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

  _objects.push_back(new Square());

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

  if (SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255) < 0) {
    std::cerr << "Could set renderer color"
      << SDL_GetError() << std::endl;
    is_inited = false;
    return is_inited;
  }

  is_inited = true;
  is_running = true;
  return is_inited;
}

void Game::Render() {
  if (SDL_RenderClear(_renderer) < 0) {
    std::cerr << "Could not rerender renderer"
      << SDL_GetError() << std::endl;
  }

  for (auto v : _objects) {
    v->Render(_renderer);
  }

  if (SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255) < 0) {
    std::cerr << "Could set renderer color"
      << SDL_GetError() << std::endl;
  }

  SDL_RenderPresent(_renderer);
}

void Game::Update() {
  for (auto v : _objects) {
    v->Update();
  }
}

bool Game::Running() {
  return is_running;
}

void Game::Clean() {
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);

  _window = NULL;
  _renderer = NULL;

  SDL_Quit();
}