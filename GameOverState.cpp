#include <iostream>
#include <memory>
#include "MenuButton.h"
#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "AnimatedGraphic.h"
#include "TextureManager.h"
#include "GameOverState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

GameOverState::GameOverState() : MenuState()
{}

void GameOverState::s_gameOverToMain()
{
    TheGame::Instance()->GetStateMachine()->ChangeState(new MainMenuState());
}

void GameOverState::s_restartPlay()
{
    TheGame::Instance()->GetStateMachine()->ChangeState(new PlayState());
}

bool GameOverState::OnEnter()
{
    StateParser stateParser;
    stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects,
        &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);

    setCallbacks(m_callbacks);

    std::cout << "entering GameOverState\n";
    return true;
}

bool GameOverState::OnExit()
{
    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearTexture(m_textureIDList[i]);
    }

    m_gameObjects.clear();

    std::cout << "exiting GameOverState\n";
    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>& callbacks)
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

void GameOverState::Update()
{
    if(!m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->Update();
        }
    }
}

void GameOverState::Render()
{
    if(!m_gameObjects.empty())
    {
        for(int i = 0; i < m_gameObjects.size(); i++)
        {
            m_gameObjects[i]->Draw();
        }
    }
}