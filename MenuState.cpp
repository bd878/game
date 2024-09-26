#include <iostream>
#include "MenuState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::Update()
{}

void MenuState::Render()
{}

bool MenuState::OnEnter()
{
    std::cout << "entering MenuState\n";
    return true;
}

bool MenuState::OnExit()
{
    std::cout << "exiting MenuState\n";
    return true;
}