#include <SDL2/SDL.h>
#include "Square.h"

void Square::Update() {
  _position += _velocity;
}

void Square::Render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  SDL_Rect r;
  r.x = (int)_position.GetX();
  r.y = (int)_position.GetY();
  r.h = _width;
  r.w = _height;

  SDL_RenderFillRect(renderer, &r);
}