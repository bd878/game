#pragma once

#include <cmath>

class Vector2D {
public:
  Vector2D() : m_x(0), m_y(0) {}

  Vector2D(float x, float y) : m_x(x), m_y(y) {}

  float GetX() const { return m_x; }
  float GetY() const { return m_y; }

  void SetX(float x) { m_x = x; }
  void SetY(float y) { m_y = y; }

  int Length() const { return std::sqrt(m_x * m_x + m_y * m_y); }

  Vector2D operator+(const Vector2D& v) { return Vector2D(m_x + v.m_x, m_y + v.m_y); };
  friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
  {
    v1.m_x += v2.m_x;
    v1.m_y += v2.m_y;

    return v1;
  };

private:
  float m_x;
  float m_y;
};