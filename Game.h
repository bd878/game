#pragma once

#include <vector>
#include <string>

#include "GameObject.h"

class Game {
public:
  static Game* Instance();

  bool Init(const std::string&, int, int, int, int, int);
  bool Running();
  void Clean();
  void Render();
  void Update();
protected:
  Game() {};
private:
  static Game* _instance;

  bool is_inited = false;
  bool is_running = false;

  SDL_Window* _window;
  SDL_Renderer* _renderer;

  std::vector<GameObject*> _objects;
};