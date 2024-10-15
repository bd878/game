#include <iostream>
#include <memory>
#include "MenuButton.h"
#include "Game.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "AnimatedGraphic.h"
#include "TextureManager.h"
#include "GameOverState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

GameOverState::GameOverState() : GameState()
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
    if(!TheTextureManager::Instance()->load("assets/gameover.png",
        "gameovertext", TheGame::Instance()->GetRenderer()))
    {
        return false;
    }

    if(!TheTextureManager::Instance()->load("assets/main.png",
        "mainbutton", TheGame::Instance()->GetRenderer()))
    {
        return false;
    }

    if(!TheTextureManager::Instance()->load("assets/restart.png",
        "restartbutton", TheGame::Instance()->GetRenderer()))
    {
        return false;
    }

    auto gameOverText = new AnimatedGraphic();
    gameOverText->Load(std::unique_ptr<LoaderParams>(
        new LoaderParams(200, 100, 190, 30, 2, "gameovertext"))
    );
    auto button1 = new MenuButton();
    button1->Load(std::unique_ptr<LoaderParams>(
        new LoaderParams(200, 200, 200, 80, 3, "mainbutton"))
    );
    button1->setCallback(s_gameOverToMain);
    auto button2 = new MenuButton();
    button2->Load(std::unique_ptr<LoaderParams>(
        new LoaderParams(200, 300, 200, 80, 3, "restartbutton"))
    );
    button2->setCallback(s_restartPlay);

    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "entering GameOverState\n";
    return true;
}

bool GameOverState::OnExit()
{
    return true;
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