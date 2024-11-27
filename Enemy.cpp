#include <iostream>
#include "ShooterObject.h"
#include "Enemy.h"

void Enemy::Load(std::unique_ptr<LoaderParams> const& pParams)
{
    ShooterObject::Load(std::move(pParams));
    m_velocity.SetY(2);
    m_velocity.SetX(0.001);
}

void Enemy::Update()
{
    m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames);

    if(m_position.GetY() < 0)
    {
        m_velocity.SetY(2);
    }
    else if(m_position.GetY() > 400)
    {
        m_velocity.SetY(-2);
    }

    ShooterObject::Update();
}