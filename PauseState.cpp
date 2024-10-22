#include <iostream>
#include "Game.h"
#include "MainMenuState.h"
#include "LoaderParams.h"
#include "StateParser.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "PauseState.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
    TheGame::Instance()->GetStateMachine()->ChangeState(new MainMenuState());
}

void PauseState::s_resumePlay()
{
    TheGame::Instance()->GetStateMachine()->PopState();
}

void PauseState::Update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Update();
    }
}

void PauseState::Render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Draw();
    }
}

bool PauseState::OnEnter()
{
    StateParser stateParser;
    stateParser.parseState("test.xml", s_pauseID, &m_gameObjects,
        &m_textureIDList);
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);

    setCallbacks(m_callbacks);

    std::cout << "entering PauseState\n";
    return true;
}

bool PauseState::OnExit()
{
    m_gameObjects.clear();
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        TheTextureManager::Instance()->clearTexture(m_textureIDList[i]);
    }
    TheInputHandler::Instance()->Reset();

    std::cout << "exiting PauseState\n";
    return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks)
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
        {
            MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton->setCallback(callbacks[pButton->getCallbackID()]);
        }
    }
}