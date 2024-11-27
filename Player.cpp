#include "Player.h"
#include "Game.h"
#include "Vector2D.h"
#include "LoaderParams.h"
#include "ShooterObject.h"
#include "InputHandler.h"

void Player::Load(std::unique_ptr<LoaderParams> const& pParams)
{
    ShooterObject::Load(std::move(pParams));
    m_moveSpeed = 3;
}

void Player::ressurect()
{
    TheGame::Instance()->SetPlayerLives(TheGame::Instance()->GetPlayerLives() - 1);

    m_position.SetX(10);
    m_position.SetY(200);
    m_bDying = false;

    m_textureId = "player";

    m_currentFrame = 0;
    m_numFrames = 5;
    m_width = 101;
    m_height = 46;

    m_dyingCounter = 0;
    m_invulnerable = false;
}

void Player::handleAnimation()
{
    // flash is invulnerable
    if(m_invulnerable)
    {
        if(m_invulnerableCounter == m_invulnerableTime)
        {
            m_invulnerable = false;
            m_invulnerableCounter = 0;
            m_alpha = 255;
        }
        else
        {
            if(m_alpha == 255)
            {
                m_alpha = 0;
            }
            else
            {
                m_alpha = 255;
            }
        }

        m_invulnerableCounter++;
    }

    // if not dead, change angle with velicoty
    if(!m_bDead)
    {
        if(m_velocity.GetX() < 0)
        {
            m_angle = -10.0;
        }
        else if (m_velocity.GetX() > 0)
        {
            m_angle = 10.0;
        }
        else
        {
            m_angle = 0.0;
        }
    }

    m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
}

void Player::Update()
{
    if(TheGame::Instance()->GetLevelComplete())
    {
        if(m_position.GetX() >= TheGame::Instance()->GetGameWidth())
        {
            TheGame::Instance()->SetCurrentLevel(TheGame::Instance()->GetCurrentLevel() + 1);
        }
        else
        {
            m_velocity.SetX(3);
            m_velocity.SetY(0);
            ShooterObject::Update();
            handleAnimation();
        }
    }
    else
    {
        // if not doing animation, update normally
        if(!m_bDying)
        {
            m_velocity.SetX(0);
            m_velocity.SetY(0);

            handleInput();

            ShooterObject::Update();

            handleAnimation();
        }
        else
        {
            m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));

            if(m_dyingCounter == m_dyingTime)
            {
                ressurect();
            }

            m_dyingCounter++;
        }
    }
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

    Vector2D* target = TheInputHandler::Instance()->getMousePosition();
    m_velocity = *target - m_position;

    m_velocity /= 50;
}