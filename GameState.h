#pragma once

#include <vector>
#include <string>

class GameState
{
public:
    virtual void Update() = 0;
    virtual void Render() = 0;

    virtual bool OnEnter() = 0;
    virtual bool OnExit() = 0;

    virtual std::string GetStateID() const = 0; 

protected:
    std::vector<std::string> m_textureIDList;
};