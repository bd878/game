#include <iostream>
#include "Game.h"
#include "MenuState.h"
#include "LoaderParams.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "PauseState.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
    TheGame::Instance()->GetStateMachine()->ChangeState(new MenuState());
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
    if (!TheTextureManager::Instance()->load("assets/resume.png",
        "resumebutton", TheGame::Instance()->GetRenderer()))
    {
        return false;
    }

    if(!TheTextureManager::Instance()->load("assets/main.png",
        "mainbutton", TheGame::Instance()->GetRenderer()))
    {
        return false;
    }

    auto button1 = new MenuButton();
    button1->Load(std::unique_ptr<LoaderParams>(new LoaderParams(200, 100,
        200, 80, 3, "mainbutton", 0)));
    button1->setCallback(s_pauseToMain);

    auto button2 = new MenuButton();
    button2->Load(std::unique_ptr<LoaderParams>(new LoaderParams(200, 300,
        200, 80, 3, "resumebutton", 0)));
    button2->setCallback(s_resumePlay);

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);

    std::cout << "entering PauseState\n";
    return true;
}

bool PauseState::OnExit()
{
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearTexture("resumebutton");
    TheTextureManager::Instance()->clearTexture("mainbutton");
    // reset the mouse button states to false
    TheInputHandler::Instance()->Reset();

    std::cout << "exiting PauseState\n";
    return true;
}
