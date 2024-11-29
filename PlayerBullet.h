#pragma once

#include "ShooterObject.h"
#include "Vector2D.h"

class PlayerBullet : public ShooterObject
{
public:

    PlayerBullet() : ShooterObject() {}

    virtual ~PlayerBullet() {}

    virtual std::string Type() { return "PlayerBullet"; }

    virtual void Load(std::unique_ptr<LoaderParams> const& pParams, Vector2D heading)
    {
        ShooterObject::Load(std::move(pParams));
        m_heading = heading;
    }

    virtual void Draw()
    {
        ShooterObject::Draw();
    }

    virtual void Collision()
    {
        m_bDead = true;
    }

    virtual void Update()
    {
        m_velocity.SetX(m_heading.GetX());
        m_velocity.SetY(m_heading.GetY());

        ShooterObject::Update();
    }

    virtual void Clean()
    {
        ShooterObject::Clean();
    }

private:

    Vector2D m_heading;
};