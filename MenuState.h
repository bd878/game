#pragma once

#include <string>
#include <vector>
#include "GameObject.h"
#include "GameState.h"

class MenuState : public GameState
{
public:

    virtual void Update();
    virtual void Render();

    virtual bool OnEnter();
    virtual bool OnExit();

    virtual std::string GetStateID() const { return s_menuID; }

private:

    static void s_menuToPlay();
    static void s_exitFromMenu();

    static const std::string s_menuID;

    std::vector<GameObject*> m_gameObjects;
};