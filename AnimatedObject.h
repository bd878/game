#pragma once

#include <memory>
#include <string>
#include <SDL2/SDL.h>

#include "LoaderParams.h"
#include "GameObject.h"

class AnimatedObject : public GameObject {
public:

  AnimatedObject() : GameObject(),
                     m_animSpeed(0),
                     m_numFrames(0),
                     m_currentFrame(0),
                     m_currentRow(0)
  {
  }

  virtual void Load(std::unique_ptr<LoaderParams> const &, SDL_Renderer*);

  virtual void Update();

  virtual void Render(SDL_Renderer*);

private:
  SDL_Texture* m_texture;

  // animation variables
  int m_animSpeed;
  int m_numFrames;
  int m_currentFrame;
  int m_currentRow;
};
