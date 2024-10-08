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
#include "GameOverState.h"

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

    if(CheckCollision(
        dynamic_cast<GameObject*>(m_gameObjects[0]),
        dynamic_cast<GameObject*>(m_gameObjects[1])))
    {
        TheGame::Instance()->GetStateMachine()->PushState(new GameOverState());
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

bool PlayState::CheckCollision(GameObject* p1, GameObject* p2)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = p1->GetPosition().GetX();
    rightA = p1->GetPosition().GetX() + p1->GetWidth();
    topA = p1->GetPosition().GetY();
    bottomA = p1->GetPosition().GetY() + p1->GetHeight();

    leftB = p2->GetPosition().GetX();
    rightB = p2->GetPosition().GetX() + p2->GetWidth();
    topB = p2->GetPosition().GetY();
    bottomB = p2->GetPosition().GetY() + p2->GetHeight();

    if (bottomA <= topB) { return false; }
    if (topA >= bottomB) { return false; }
    if (rightA <= leftB) { return false; }
    if (leftA >= rightB) { return false; }

    return true;
}