#pragma once

#include <vector>
#include <string>
#include "GameObject.h"
#include "GameState.h"

class GameOverState : public GameState
{
public:

    GameOverState();

    virtual ~GameOverState() {};

    virtual void Update();

    virtual void Render();
 
    virtual bool OnEnter();

    virtual bool OnExit();

    virtual std::string GetStateID() const { return s_gameOverID; }

private:
    static void s_gameOverToMain();
    static void s_restartPlay();

    static const std::string s_gameOverID;

    std::vector<GameObject*> m_gameObjects;
};