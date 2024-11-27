#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector2D.h"
#include "Game.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "ShooterObject.h"

void ShooterObject::Load(std::unique_ptr<LoaderParams> const &params)
{
  m_numFrames = params->GetNumFrames();
  m_position = Vector2D(params->GetX(), params->GetY());
  m_width = params->GetWidth();
  m_height = params->GetHeight();
  m_textureId = params->GetTextureId();
}

void AnimatedObject::Update()
{
  m_position += m_velocity;
  m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedObject::Draw()
{
  if(m_velocity.GetX() < 0)
  {
    TheTextureManager::Instance()->drawFrame(m_textureId,
      m_position.GetX(), m_position.GetY(),
      m_width, m_height, m_currentRow, m_currentFrame,
      TheGame::Instance()->GetRenderer(), SDL_FLIP_HORIZONTAL);
  }
  else
  {
    TheTextureManager::Instance()->drawFrame(m_textureId,
      m_position.GetX(), m_position.GetY(), m_width, m_height,
      m_currentRow, m_currentFrame, TheGame::Instance()->GetRenderer(), SDL_FLIP_NONE);
  }
}
