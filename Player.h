#pragma once

#include <memory>
#include "LoaderParams.h"
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Player : public ShooterObject {

public:

    virtual ~Player() {}

    virtual void Load(std::unique_ptr<LoaderParams> const& pParams);

    virtual void Update();

private:
    void ressurect();

    void handleInput();

    void handleAnimation();

    int m_invulnerable;
    int m_invulnerableTime;
    int m_invulnerableCounter;
};

class PlayerCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Player();
    }
};