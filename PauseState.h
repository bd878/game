#pragma once

#include <string>
#include "GameState.h"
#include "GameObject.h"

class PauseState : public GameState
{

public:
    virtual void Update();
    virtual void Render();

    virtual bool OnEnter();
    virtual bool OnExit();

    virtual std::string GetStateID() const { return s_pauseID; }

private:

    static void s_pauseToMain();
    static void s_resumePlay();

    static const std::string s_pauseID;

    std::vector<GameObject*> m_gameObjects;
};