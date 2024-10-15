#pragma once

#include <string>

class LoaderParams
{
public:
  LoaderParams(
    int x,
    int y,
    int width,
    int height,
    int numFrames,
    std::string textureId,
    int callbackID = 0,
    int animSpeed = 1
  ) :
  m_x(x),
  m_y(y),
  m_width(width),
  m_height(height),
  m_numFrames(numFrames),
  m_callbackID(callbackID),
  m_textureId(textureId),
  m_animSpeed(animSpeed)
  {
  }

  int GetX() const { return m_x; }
  int GetY() const { return m_y; }

  int GetWidth() const { return m_width; }
  int GetHeight() const { return m_height; }

  std::string GetTextureId() const { return m_textureId; }
  int GetCallbackID() const { return m_callbackID; }

  int GetAnimSpeed() const { return m_animSpeed; }
  int GetNumFrames() const { return m_numFrames; }

private:
  int m_x;
  int m_y;

  int m_width;
  int m_height;

  int m_callbackID;

  int m_animSpeed;
  int m_numFrames;

  std::string m_textureId;
};
