#include <iostream>
#include "Level.h"

Level::~Level()
{
    for(int i = 0; i < m_layers.size(); i++)
    {
        delete m_layers[i];
    }
    m_layers.clear();
}

void Level::render()
{
    std::cout << "Render level, layers: " << m_layers.size() << std::endl;
    for(int i = 0; i < m_layers.size(); i++)
    {
        m_layers[i]->render();
    }
}

void Level::update()
{
    for(int i = 0; i < m_layers.size(); i++)
    {
        m_layers[i]->update();
    }
}