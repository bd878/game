#include <string>
#include <iostream>
#include "PlayState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::Update()
{}

void PlayState::Render()
{}

bool PlayState::OnEnter()
{
    std::cout << "entering PlayState\n";
    return true;
}

bool PlayState::OnExit()
{
    std::cout << "exiting PlayState\n";
    return true;
}