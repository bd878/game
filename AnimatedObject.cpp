#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector2D.h"
#include "LoaderParams.h"
#include "AnimatedObject.h"

void AnimatedObject::Load(std::unique_ptr<LoaderParams> const &params, SDL_Renderer* renderer)
{
  SDL_Surface* pTempSurface = IMG_Load(params->GetFileName().c_str());
  if (pTempSurface == 0)
  {
    std::cout << IMG_GetError() << std::endl;
    return;
  }

  m_animSpeed = params->GetAnimSpeed();
  m_numFrames = params->GetNumFrames();
  m_position = Vector2D(params->GetX(), params->GetY());
  m_width = params->GetWidth();
  m_height = params->GetHeight();

  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pTempSurface);

  SDL_FreeSurface(pTempSurface);

  if (pTexture == NULL)
  {
    std::cout << "Unable to create a texture " << IMG_GetError()
      << std::endl;
    return;
  }

  m_texture = pTexture;
}

void AnimatedObject::Update()
{
  m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedObject::Render(SDL_Renderer* renderer)
{
  SDL_Rect srcRect;
  SDL_Rect dstRect;

  srcRect.x = m_width * m_currentFrame;
  srcRect.y = m_height * m_currentRow;
  srcRect.w = dstRect.w = m_width;
  srcRect.h = dstRect.h = m_height;
  dstRect.x = m_position.GetX();
  dstRect.y = m_position.GetY();

  SDL_RenderCopyEx(renderer, m_texture, &srcRect, &dstRect, 0, 0, SDL_FLIP_NONE);
}