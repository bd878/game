#include "InputHandler.h"
#include "Vector2D.h"
#include "LoaderParams.h"
#include "MenuButton.h"

MenuButton::MenuButton() : ShooterObject()
{}

void MenuButton::Load(std::unique_ptr<LoaderParams> const &pParams)
{
    ShooterObject::Load(std::move(pParams));
    m_callbackID = pParams->GetCallbackID();
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::Draw()
{
    ShooterObject::Draw();
}

void MenuButton::Update()
{
    Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

    if(pMousePos->GetX() < (m_position.GetX() + m_width)
    && pMousePos->GetX() > m_position.GetX()
    && pMousePos->GetY() < (m_position.GetY() + m_height)
    && pMousePos->GetY() > m_position.GetY())
    {
        m_currentFrame = MOUSE_OVER;

        if(TheInputHandler::Instance()->getMouseButtonState(LEFT))
        {
            m_currentFrame = CLICKED;

            m_callback();

            m_bReleased = false;
        }
        else if(!TheInputHandler::Instance()->getMouseButtonState(LEFT))
        {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
    }
}
