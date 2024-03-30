#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "LoaderParams.h"
#include "GameObject.h"
#include "Vector2D.h"

class Square : public GameObject {
public:
  Square() : GameObject()
  {
  };

  virtual void Load(std::unique_ptr<LoaderParams> const &, SDL_Renderer*);

  virtual void Update();

  virtual void Render(SDL_Renderer*);
};
