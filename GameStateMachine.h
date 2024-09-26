#pragma once

#include <vector>
#include "GameState.h"

class GameStateMachine
{
public:

    void PushState(GameState* pState);
    void ChangeState(GameState* pState);
    void PopState();

    std::vector<GameState*>& GetGameStates() { return m_gameStates; }

private:
    std::vector<GameState*> m_gameStates;
};