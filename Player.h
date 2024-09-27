#pragma once

#include <memory>
#include "LoaderParams.h"
#include "AnimatedObject.h"

class Player : public AnimatedObject {

public:

    virtual ~Player() {}

    virtual void Load(std::unique_ptr<LoaderParams> const& pParams);

    virtual void Update();

private:
    void handleInput();
};