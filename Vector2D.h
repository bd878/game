#pragma once

class Vector2D {
public:
  Vector2D() : _x(0), _y(0) {}
  Vector2D(float x, float y) : _x(x), _y(y) {}
  Vector2D& operator=(const Vector2D&);

  float GetX() { return _x; }
  float GetY() { return _y; }

  Vector2D operator+(const Vector2D&);
  friend Vector2D& operator+=(Vector2D&, const Vector2D&);

private:
  float _x;
  float _y;
};