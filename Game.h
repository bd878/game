#pragma once

#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include "GameStateMachine.h"
#include "GameObject.h"

class Game {
public:
  static Game* Instance();

  bool Init(const std::string&, int, int, int, int, int);
  bool Running();
  void Clean();
  void Render();
  void Update();
  void HandleEvents();
  void Quit();

  int GetGameWidth() const { return m_gameWidth; }
  int GetGameHeight() const { return m_gameHeight; }

  int GetScrollSpeed() const { return m_scrollSpeed; }

  void SetPlayerLives(int lives) { m_playerLives = lives; }
  int GetPlayerLives() const { return m_playerLives; }

  void SetLevelComplete(bool levelComplete) { m_bLevelComplete = levelComplete; }
  const bool GetLevelComplete() { return m_bLevelComplete; }

  void SetCurrentLevel(int);
  int GetCurrentLevel() const { return m_currentLevel; };

  GameStateMachine* GetStateMachine() { return m_pGameStateMachine; }
  SDL_Renderer* GetRenderer() const { return _renderer; }
  SDL_Window* GetWindow() const { return _window; }

protected:
  Game() {};
private:
  inline static Game* _instance = nullptr;

  bool _inited = false;
  bool _running = false;

  int m_gameWidth;
  int m_gameHeight;

  int m_scrollSpeed;

  int m_playerLives;

  bool m_bLevelComplete;

  int m_currentLevel;

  SDL_Window* _window;
  SDL_Renderer* _renderer;

  GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;
