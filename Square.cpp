#include <SDL2/SDL.h>
#include "Square.h"
#include "Vector2D.h"

void Square::Load(std::unique_ptr<LoaderParams> const &params, SDL_Renderer*)
{
  m_position = Vector2D(params->GetX(), params->GetY());
  m_width = params->GetWidth();
  m_height = params->GetHeight();
}

void Square::Update()
{
  m_position += m_velocity;
}

void Square::Render(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  SDL_Rect r;
  r.x = (int)m_position.GetX();
  r.y = (int)m_position.GetY();
  r.h = m_height;
  r.w = m_width;

  SDL_RenderFillRect(renderer, &r);
}