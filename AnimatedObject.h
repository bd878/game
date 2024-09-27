#pragma once

#include <memory>
#include <string>
#include <SDL2/SDL.h>

#include "LoaderParams.h"
#include "GameObject.h"

class AnimatedObject : public GameObject {
public:
  virtual ~AnimatedObject() {}

  virtual void Load(std::unique_ptr<LoaderParams> const&);

  virtual void Update();

  virtual void Draw();

protected:

  AnimatedObject() : GameObject(),
                     m_animSpeed(0),
                     m_numFrames(0),
                     m_currentFrame(0),
                     m_currentRow(0),
                     m_moveSpeed(0)
  {
  }

  // animation variables
  int m_animSpeed;
  int m_numFrames;
  int m_currentFrame;
  int m_currentRow;
  int m_moveSpeed;
};
