#include <iostream>
#include "GameObject.h"
#include "Game.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "MenuState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::Update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Update();
    }
}

void MenuState::Render()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Draw();
    }
}

bool MenuState::OnEnter()
{
    std::cout << "on menu state enter\n";
    if(!TheTextureManager::Instance()->load("./assets/button.png",
        "playbutton", TheGame::Instance()->GetRenderer()))
    {
        std::cerr << "failed to load button.png\n";
        return false;
    }

    if(!TheTextureManager::Instance()->load("./assets/exit.png",
        "exitbutton", TheGame::Instance()->GetRenderer()))
    {
        std::cerr << "failed to load exit button\n";
        return false;
    }

    GameObject* button1 = new MenuButton();
    button1->Load(std::unique_ptr<LoaderParams>(new LoaderParams(100, 100, 400, 100, 3, "playbutton", 0)));

    GameObject* button2 = new MenuButton();
    button2->Load(std::unique_ptr<LoaderParams>(new LoaderParams(100, 300, 400, 100, 3, "exitbutton", 0)));

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::OnExit()
{
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearTexture("playbutton");
    TheTextureManager::Instance()->clearTexture("exitbutton");
    return true;
}