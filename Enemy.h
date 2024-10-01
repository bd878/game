#pragma once

#include <memory>
#include "LoaderParams.h"
#include "AnimatedObject.h"

class Enemy : public AnimatedObject {
public:
    virtual ~Enemy() {}

    virtual void Load(std::unique_ptr<LoaderParams> const& pParams);

    virtual void Update();
};