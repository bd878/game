#pragma once

#include <memory>
#include "LoaderParams.h"
#include "AnimatedObject.h"
#include "GameObjectFactory.h"

class Enemy : public AnimatedObject {
public:
    virtual ~Enemy() {}

    virtual void Load(std::unique_ptr<LoaderParams> const& pParams);

    virtual void Update();
};

class EnemyCreator : public BaseCreator {
    GameObject* createGameObject() const
    {
        return new Enemy();
    }
};