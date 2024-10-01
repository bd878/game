#include <string>
#include <iostream>
#include "Game.h"
#include "LoaderParams.h"
#include "Player.h"
#include "InputHandler.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "PlayState.h"
#include "PauseState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::Update()
{
    if(TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance()->GetStateMachine()->PushState(new PauseState());
    }

    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Update();
    }
}

void PlayState::Render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Draw();
    }
}

bool PlayState::OnEnter()
{
    if(!TheTextureManager::Instance()->load("./assets/heli.png",
        "helicopter", TheGame::Instance()->GetRenderer()))
    {
        return false;
    }

    if(!TheTextureManager::Instance()->load("./assets/helicopter2.png",
        "helicopter2", TheGame::Instance()->GetRenderer()))
    {
        return false;
    }

    auto player = new Player();
    player->Load(std::unique_ptr<LoaderParams>(new LoaderParams(500, 100, 101, 55, 5, "helicopter", 3)));
    auto enemy = new Enemy();
    enemy->Load(std::unique_ptr<LoaderParams>(new LoaderParams(100, 100, 128, 55, 5, "helicopter2", 3)));

    m_gameObjects.push_back(player);
    m_gameObjects.push_back(enemy);

    std::cout << "entering play state\n";
    return true;
}

bool PlayState::OnExit()
{
    m_gameObjects.clear();
    TheTextureManager::Instance()
        ->clearTexture("helicopter");

    std::cout << "exiting PlayState\n";
    return true;
}