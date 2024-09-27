#include "GameStateMachine.h"

void GameStateMachine::PushState(GameState *pState)
{
    m_gameStates.push_back(pState);
    m_gameStates.back()->OnEnter();
}

void GameStateMachine::PopState()
{
    if(!m_gameStates.empty())
    {
        if(m_gameStates.back()->OnExit())
        {
            delete m_gameStates.back();
            m_gameStates.pop_back();
        }
    }
}

void GameStateMachine::ChangeState(GameState *pState)
{
    if(!m_gameStates.empty())
    {
        if(m_gameStates.back()->GetStateID() == pState->GetStateID())
        {
            return;
        }

        m_gameStates.back()->OnExit();
        m_gameStates.pop_back();
    }

    pState->OnEnter();

    m_gameStates.push_back(pState);
}

void GameStateMachine::Update()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->Update();
    }
}

void GameStateMachine::Render()
{
    if(!m_gameStates.empty())
    {
        m_gameStates.back()->Render();
    }
}