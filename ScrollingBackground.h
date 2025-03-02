#pragma once

#include <iostream>
#include "GameObjectFactory.h"
#include "ShooterObject.h"

class ScrollingBackground : public ShooterObject
{
public:

    virtual ~ScrollingBackground() {}
    ScrollingBackground();

    virtual void Draw();
    virtual void Update();
    virtual void Clean();

    virtual void Load(std::unique_ptr<LoaderParams> const&);

private:

    int m_scrollSpeed;

    int count;
    int maxcount;

    SDL_Rect m_srcRect1;
    SDL_Rect m_srcRect2;

    SDL_Rect m_destRect1;
    SDL_Rect m_destRect2;

    int m_srcRect1Width;
    int m_srcRect2Width;

    int m_destRect1Width;
    int m_destRect2Width;
};

class ScrollingBackgroundCreator : public BaseCreator
{
public:

    virtual GameObject* createGameObject() const
    {
        return new ScrollingBackground();
    }
};