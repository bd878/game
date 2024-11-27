#pragma once

#include <memory>
#include "GameObjectFactory.h"
#include "LoaderParams.h"
#include "ShooterObject.h"

class MenuButton : public ShooterObject
{
public:
    MenuButton();

    virtual ~MenuButton() {}

    virtual void Load(std::unique_ptr<LoaderParams> const &);

    virtual void Draw();
    virtual void Update();

    void setCallback(void(*callback)()) { m_callback = callback; }
    int getCallbackID() { return m_callbackID; }

private:
    enum button_state
    {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };

    bool m_bReleased;

    int m_callbackID;

    void (*m_callback)();
};

class MenuButtonCreator : public BaseCreator {
    virtual GameObject* createGameObject() const {
        return new MenuButton();
    }
};