#pragma once

#include <vector>
#include <string>
#include "GameState.h"

class PlayState : public GameState
{
public:

    virtual void Update();
    virtual void Render();

    virtual bool OnEnter();
    virtual bool OnExit();

    virtual std::string GetStateID() const { return s_playID; }

private:
    static const std::string s_playID;

    std::vector<GameObject*> m_gameObjects;
};