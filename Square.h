#pragma once

#include <SDL2/SDL.h>
#include "GameObject.h"
#include "Vector2D.h"

class Square : public GameObject {
public:
  Square() : _velocity(1, 1), _position(0, 0), _width(10), _height(10) {};

  virtual void Update();
  virtual void Render(SDL_Renderer*);

protected:
  Vector2D _velocity;
  Vector2D _position;

  int _width;
  int _height;
};
