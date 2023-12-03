#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"
#include "Square.h"
#include "InputHandler.h"

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
    _inited = false;
    return _inited;
  }

  _objects.push_back(new Square());

  _window = SDL_CreateWindow(title.c_str(),
    x, y, w, h, flags);

  if (_window == NULL) {
    std::cerr << "Window could not be created"
      << SDL_GetError() << std::endl;
    _inited = false;
    return _inited;
  }

  _renderer = SDL_CreateRenderer(_window, -1, 0);
  if (_renderer == NULL) {
    std::cerr << "Renderer could not be created"
      << SDL_GetError() << std::endl;
    _inited = false;
    return _inited;
  }

  if (SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255) < 0) {
    std::cerr << "Could set renderer color"
      << SDL_GetError() << std::endl;
    _inited = false;
    return _inited;
  }

  _inited = true;
  _running = true;
  return _inited;
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

void Game::HandleEvents() {
  TheInputHandler::Instance()->HandleEvents();
}

void Game::Update() {
  for (auto v : _objects) {
    v->Update();
  }
}

bool Game::Running() {
  return _running;
}

void Game::Clean() {
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);

  _window = NULL;
  _renderer = NULL;

  SDL_Quit();
}

void Game::Quit() {
  std::cout << "Quit" << std::endl;
  _running = false;
}