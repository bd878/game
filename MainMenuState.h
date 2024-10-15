#pragma once

#include "GameObject.h"
#include "MenuState.h"

class MainMenuState : public MenuState
{
public:

    virtual ~MainMenuState() {}

    virtual void Update();
    virtual void Render();

    virtual bool OnEnter();
    virtual bool OnExit();

    virtual std::string GetStateID() const { return s_menuID; }

protected:
    virtual void setCallbacks(const std::vector<Callback>& callbacks);

    static void s_menuToPlay();
    static void s_exitFromMenu();

    static const std::string s_menuID;

    std::vector<GameObject*> m_gameObjects;
};