#pragma once

#include <memory>
#include "LoaderParams.h"
#include "AnimatedObject.h"

class MenuButton : public AnimatedObject
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