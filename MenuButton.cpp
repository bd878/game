#include "InputHandler.h"
#include "Vector2D.h"
#include "LoaderParams.h"
#include "MenuButton.h"

MenuButton::MenuButton() : AnimatedObject()
{}

void MenuButton::Load(std::unique_ptr<LoaderParams> const &pParams)
{
    AnimatedObject::Load(std::move(pParams));
    m_currentFrame = MOUSE_OUT;
}

void MenuButton::Draw()
{
    AnimatedObject::Draw();
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
