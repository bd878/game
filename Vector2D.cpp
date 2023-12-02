#include "Vector2D.h"

Vector2D& Vector2D::operator=(const Vector2D& v) {
  if (this == &v) {
    return *this;
  }

  _x = v._x;
  _y = v._y;

  return *this;
}

Vector2D Vector2D::operator+(const Vector2D& v) {
  return Vector2D(_x + v._x, _y + v._y);
}

Vector2D& operator+=(Vector2D& v1, const Vector2D& v2) {
  v1._x += v2._x;
  v1._y += v2._y;

  return v1;
}