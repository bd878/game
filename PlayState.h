#pragma once

#include <vector>
#include <string>
#include "Level.h"
#include "GameObject.h"
#include "GameState.h"

class PlayState : public GameState
{
public:

    virtual ~PlayState() { delete pLevel; }

    virtual void Update();
    virtual void Render();

    virtual bool OnEnter();
    virtual bool OnExit();

    virtual std::string GetStateID() const { return s_playID; }

    bool CheckCollision(GameObject* p1, GameObject* p2);

private:
    static const std::string s_playID;

    std::vector<GameObject*> m_gameObjects;

    Level* pLevel;
};