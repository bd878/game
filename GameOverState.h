#pragma once

#include <vector>
#include <string>
#include "GameObject.h"
#include "MenuState.h"

class GameOverState : public MenuState
{
public:

    GameOverState();

    virtual ~GameOverState() {};

    virtual void Update();

    virtual void Render();
 
    virtual bool OnEnter();

    virtual bool OnExit();

    virtual std::string GetStateID() const { return s_gameOverID; }

protected:

    virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
    static void s_gameOverToMain();
    static void s_restartPlay();

    static const std::string s_gameOverID;

    std::vector<GameObject*> m_gameObjects;
};