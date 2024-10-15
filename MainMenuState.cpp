#include <iostream>
#include "GameObject.h"
#include "Game.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "StateParser.h"
#include "MainMenuState.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::Update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Update();
    }
}

void MainMenuState::Render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Draw();
    }
}

bool MainMenuState::OnEnter()
{
    StateParser stateParser;
    if (!stateParser.parseState("test.xml", s_menuID, &m_gameObjects,
        &m_textureIDList)) {
        std::cout << "failed to parse state\n";
    }
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    setCallbacks(m_callbacks);
    return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
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

bool MainMenuState::OnExit()
{
    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearTexture(m_textureIDList[i]);
    }

    m_gameObjects.clear();

    std::cout << "exiting MainMenuState\n";
    return true;
}

void MainMenuState::s_menuToPlay()
{
    TheGame::Instance()->GetStateMachine()->ChangeState(new PlayState());
}

void MainMenuState::s_exitFromMenu()
{
    TheGame::Instance()->Quit();
}