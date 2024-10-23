#include <iostream>
#include "ObjectLayer.h"

void ObjectLayer::update()
{
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        m_gameObjects[i]->Update();
    }
}

void ObjectLayer::render()
{
    std::cout << "render object layer" << std::endl;
    for (int i = 0; i < m_gameObjects.size(); ++i)
    {
        m_gameObjects[i]->Draw();
    }
}