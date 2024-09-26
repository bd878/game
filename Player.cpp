#include "Player.h"
#include "Game.h"
#include "LoaderParams.h"
#include "AnimatedObject.h"
#include "InputHandler.h"

void Player::Load(std::unique_ptr<LoaderParams> const& pParams)
{
    AnimatedObject::Load(std::move(pParams));
    m_moveSpeed = 3;
}

void Player::Update()
{
    m_velocity.SetX(0);
    m_velocity.SetY(0);

    handleInput();

    AnimatedObject::Update();
}

void Player::handleInput()
{
    if(TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP) && m_position.GetY() > 0)
    {
        m_velocity.SetY(-m_moveSpeed);
    }
    else if(TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN) && (m_position.GetY() + m_height) < TheGame::Instance()->GetGameHeight() - 10)
    {
        m_velocity.SetY(m_moveSpeed);
    }

    if(TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT) && m_position.GetX() > 0)
    {
        m_velocity.SetX(-m_moveSpeed);
    }
    else if(TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT) && (m_position.GetX() + m_width) < TheGame::Instance()->GetGameWidth())
    {
        m_velocity.SetX(m_moveSpeed);
    }
}