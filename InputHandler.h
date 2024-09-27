#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "Vector2D.h"

enum mouse_buttons
{
  LEFT = 0,
  MIDDLE = 1,
  RIGHT = 2
};

class InputHandler {
public:
  static InputHandler* Instance();

  void Update();
  void Reset();

  bool IsKeyDown(SDL_Scancode) const;

  Vector2D* getMousePosition() const;
  bool getMouseButtonState(int) const;

private:

  InputHandler();
  ~InputHandler();

  InputHandler(const InputHandler&);
  InputHandler& operator=(const InputHandler&);

  void onKeyDown();
  void onKeyUp();

  void onMouseMove(SDL_Event&);
  void onMouseButtonUp(SDL_Event&);
  void onMouseButtonDown(SDL_Event&);

  // keyboard specific
  const Uint8* m_keystates;

  // mouse specific
  std::vector<bool> m_mouseButtonStates;
  Vector2D* m_mousePosition;

  inline static InputHandler* s_pInstance = nullptr;
};

typedef InputHandler TheInputHandler;
