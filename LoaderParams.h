#pragma once

#include <string>

class LoaderParams
{
public:
  LoaderParams(int x, int y, int width, int height, int numFrames,
               std::string fileName, int animSpeed = 0) :
  m_x(x),
  m_y(y),
  m_width(width),
  m_height(height),
  m_numFrames(numFrames),
  m_fileName(fileName),
  m_animSpeed(animSpeed)
  {
  }

  int GetX() const { return m_x; }
  int GetY() const { return m_y; }

  int GetWidth() const { return m_width; }
  int GetHeight() const { return m_height; }

  std::string GetFileName() const { return m_fileName; }

  int GetAnimSpeed() const { return m_animSpeed; }
  int GetNumFrames() const { return m_numFrames; }

private:
  int m_x;
  int m_y;

  int m_width;
  int m_height;

  int m_animSpeed;

  std::string m_fileName;

  int m_numFrames;
};
