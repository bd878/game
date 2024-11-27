#pragma once

#include "LoaderParams.h"
#include "Vector2D.h"
#include <string>
#include <memory>
#include <SDL2/SDL.h>

class GameObject {
public:
  virtual ~GameObject() {}

  virtual void Load(std::unique_ptr<LoaderParams> const &) = 0;

  virtual void Update() = 0;

  virtual void Draw() = 0;

  virtual void Clean() = 0;

  virtual void Collision() = 0;

  virtual std::string Type() = 0;

  virtual Vector2D& GetPosition() { return m_position; }

  int GetWidth() { return m_width; }

  int GetHeight() { return m_height; }

  void Scroll(float scrollSpead) { m_position.SetX(m_position.GetX() - scrollSpead); }

  bool Updating() { return m_bUpdating; }

  bool Dead() { return m_bDead; }

  bool Dying() { return m_bDying; }

  void SetUpdating(bool updating) { m_bUpdating = updating; }

protected:

  // defaults
  GameObject() : m_position(0, 0),
                 m_velocity(0, 0),
                 m_width(0),
                 m_height(0),
                 m_currentRow(0),
                 m_currentFrame(0),
                 m_bUpdating(false),
                 m_bDead(false),
                 m_bDying(false),
                 m_angle(0),
                 m_alpha(255)
  {
  }

  // coords
  Vector2D m_position;
  Vector2D m_velocity;
  Vector2D m_acceleration;

  // size variables
  int m_width;
  int m_height;

  int m_currentRow;
  int m_currentFrame;
  int m_numFrames;

  std::string m_textureId;

  bool m_bUpdating;
  bool m_bDead;
  bool m_bDying;

  double m_angle;

  int m_alpha;
};
