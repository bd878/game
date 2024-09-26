#include <string>
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include "Player.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "LoaderParams.h"
#include "PlayState.h"
#include "MenuState.h"
#include "GameStateMachine.h"

Game* Game::Instance() {
  if (_instance == nullptr) {
    _instance = new Game;
  }
  return _instance;
}

bool Game::Init(const std::string& title, int xpos, int ypos, int width, int height, int flags) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "SDL2 could not be initialized"
      << SDL_GetError() << std::endl;
    _inited = false;
    return _inited;
  }

  m_gameWidth = width;
  m_gameHeight = height;

  m_pGameStateMachine = new GameStateMachine();
  m_pGameStateMachine->ChangeState(new MenuState());

  _window = SDL_CreateWindow(title.c_str(),
    xpos, ypos, width, height, flags);

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

  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    std::cerr << "SDL_image could not be initialized"
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

  TheTextureManager::Instance()->load("./assets/animate-alpha.png", "animate", _renderer);

  auto player = new Player();
  player->Load(std::unique_ptr<LoaderParams>(new LoaderParams(0, 0, 128, 100, 6, "animate", 6)));
  _objects.push_back(player);

  _inited = true;
  _running = true;
  return _inited;
}

void Game::Render() {
  if (SDL_RenderClear(_renderer) < 0) {
    std::cerr << "Could not rerender renderer"
      << SDL_GetError() << std::endl;
    return;
  }

  for (auto v : _objects) {
    v->Draw();
  }

  if (SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0) < 0) {
    std::cerr << "Could set renderer color"
      << SDL_GetError() << std::endl;
  }

  SDL_RenderPresent(_renderer);
}

void Game::HandleEvents() {
  TheInputHandler::Instance()->Update();

  if(TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RETURN))
  {
    m_pGameStateMachine->ChangeState(new PlayState());
  }
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
  std::cout << "clean game" << std::endl;

  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);

  _window = NULL;
  _renderer = NULL;

  IMG_Quit();
  SDL_Quit();
}

void Game::Quit() {
  std::cout << "Quit" << std::endl;
  _running = false;
}