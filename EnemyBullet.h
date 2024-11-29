#pragma once

#include "PlayerBullet.h"

class EnemyBullet : public PlayerBullet
{
public:

    EnemyBullet() : PlayerBullet()
    {}

    virtual ~EnemyBullet() {}

    virtual std::string Type() { return "EnemyBullet"; }
};