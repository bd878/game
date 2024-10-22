#pragma once

#include <memory>
#include "GameObjectFactory.h"
#include "LoaderParams.h"
#include "AnimatedObject.h"

class AnimatedGraphic : public AnimatedObject
{
public:
    AnimatedGraphic();

    virtual ~AnimatedGraphic() {}

    virtual void Load(std::unique_ptr<LoaderParams> const&);

    virtual void Update();

private:
    int m_animSpeed;
    int m_currentFrame;
};

class AnimatedGraphicCreator : public BaseCreator
{
public:

    virtual GameObject* createGameObject() const
    {
        return new AnimatedGraphic();
    }
};