#pragma once

#include <memory>
#include <string>
#include <SDL2/SDL.h>

#include "LoaderParams.h"
#include "GameObject.h"

class ShooterObject : public GameObject {
public:
  virtual ~ShooterObject() {}

  virtual void Load(std::unique_ptr<LoaderParams> const&);

  virtual void Update();

  virtual void Draw();

  virtual void Clean() {}

  virtual void Collision() {}

  virtual std::string Type() { return "SDLGameObject"; }

protected:

  ShooterObject() {};

  void DoDyingAnimation();

  int m_bulletFiringSpeed;
  int m_bulletCounter;

  int m_moveSpeed;

  int m_dyingTime;
  int m_dyingCounter;

  bool m_bPlayedDeathSound;
};
