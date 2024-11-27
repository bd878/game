#pragma once

#include <string>
#include <memory>
#include "LoaderParams.h"
#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Enemy : public ShooterObject {
public:

    Enemy() : ShooterObject() {}

    virtual void Load(std::unique_ptr<LoaderParams> const& pParams);

    virtual void Update();

    virtual std::string Type() { return "Enemy"; }

protected:
    int m_health;

    virtual ~Enemy() {}
};

class EnemyCreator : public BaseCreator {
    GameObject* createGameObject() const
    {
        return new Enemy();
    }
};