#pragma once

#include <SDL2/SDL.h>

class GameObject {
public:
  virtual void Update() = 0;
  virtual void Render(SDL_Renderer*) = 0;

protected:
  virtual ~GameObject() = default;
};
