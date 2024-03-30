#pragma once

#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include "GameObject.h"

class Game {
public:
  static Game* Instance();

  bool Init(const std::string&, int, int, int, int, int);
  bool Running();
  void Clean();
  void Render();
  void Update();
  void HandleEvents();
  void Quit();

  SDL_Renderer* GetRenderer() const { return _renderer; }
  SDL_Window* GetWindow() const { return _window; }

protected:
  Game() {};
private:
  inline static Game* _instance = nullptr;

  bool _inited = false;
  bool _running = false;

  SDL_Window* _window;
  SDL_Renderer* _renderer;

  std::vector<GameObject*> _objects;
};

typedef Game TheGame;
