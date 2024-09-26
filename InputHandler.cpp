#include <iostream>
#include <SDL2/SDL.h>
#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::Instance() {
  if (s_pInstance == nullptr) {
    s_pInstance = new InputHandler;
  }
  return s_pInstance;
}

InputHandler::InputHandler() : m_keystates(0),
m_mousePosition(new Vector2D(0,0))
{
  for (int i = 0; i < 3; ++i)
  {
    m_mouseButtonStates.push_back(false);
  }
}

InputHandler::~InputHandler()
{
  delete m_mousePosition;
  delete m_keystates;

  m_mouseButtonStates.clear();
}

void InputHandler::Update() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_QUIT:
        TheGame::Instance()->Quit();
        break;

      case SDL_MOUSEMOTION:
        onMouseMove(e);
        break;

      case SDL_MOUSEBUTTONUP:
        onMouseButtonUp(e);
        break;

      case SDL_MOUSEBUTTONDOWN:
        onMouseButtonDown(e);
        break;

      case SDL_KEYUP:
        onKeyUp();
        break;

      case SDL_KEYDOWN:
        onKeyDown();
        break;

      default:
        break;
    }
  }
}

void InputHandler::Reset()
{
  m_mouseButtonStates[LEFT] = false;
  m_mouseButtonStates[RIGHT] = false;
  m_mouseButtonStates[MIDDLE] = false;
}

bool InputHandler::IsKeyDown(SDL_Scancode key) const
{
  if(m_keystates != 0)
  {
    if(m_keystates[key] == 1)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
}

bool InputHandler::getMouseButtonState(int buttonNumber) const
{
  return m_mouseButtonStates[buttonNumber];
}

Vector2D* InputHandler::getMousePosition() const
{
  return m_mousePosition;
}

void InputHandler::onKeyDown()
{
  m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
  m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseMove(SDL_Event &event)
{
  m_mousePosition->SetX(event.motion.x);
  m_mousePosition->SetY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event &event)
{
  if(event.button.button == SDL_BUTTON_LEFT)
  {
    m_mouseButtonStates[LEFT] = true;
  }

  if(event.button.button == SDL_BUTTON_MIDDLE)
  {
    m_mouseButtonStates[MIDDLE] = true;
  }

  if(event.button.button == SDL_BUTTON_RIGHT)
  {
    m_mouseButtonStates[RIGHT] = true;
  }
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
  if(event.button.button == SDL_BUTTON_LEFT)
  {
    m_mouseButtonStates[LEFT] = false;
  }

  if(event.button.button == SDL_BUTTON_MIDDLE)
  {
    m_mouseButtonStates[MIDDLE] = false;
  }

  if(event.button.button == SDL_BUTTON_RIGHT)
  {
    m_mouseButtonStates[RIGHT] = false;
  }
}