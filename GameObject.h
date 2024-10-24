#pragma once

#include "LoaderParams.h"
#include "Vector2D.h"
#include <string>
#include <memory>
#include <SDL2/SDL.h>

class GameObject {
public:
  virtual void Load(std::unique_ptr<LoaderParams> const &) = 0;

  virtual void Update() = 0;

  virtual void Draw() = 0;

  virtual Vector2D& GetPosition() { return m_position; }

  virtual int GetWidth() { return m_width; }

  virtual int GetHeight() { return m_height; }

protected:
  virtual ~GameObject() {}

  // defaults
  GameObject() : m_position(0, 0),
                 m_velocity(0, 0),
                 m_width(0),
                 m_height(0)
  {
  }

  // coords
  Vector2D m_position;
  Vector2D m_velocity;

  // size variables
  int m_width;
  int m_height;

  std::string m_textureId;
};
