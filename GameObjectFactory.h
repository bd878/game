#pragma once

#include <string>
#include <iostream>
#include <map>
#include "GameObject.h"

class BaseCreator
{
public:

    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:

    static GameObjectFactory* Instance()
    {
        if(pInstance == 0)
        {
            pInstance = new GameObjectFactory();
        }
        return pInstance;
    }

    bool registerType(std::string typeID, BaseCreator* pCreator)
    {
        auto it = m_creators.find(typeID);

        if(it != m_creators.end())
        {
            delete pCreator;
            return false;
        }

        m_creators[typeID] = pCreator;

        return true;
    }

    GameObject* create(std::string typeID)
    {
        auto it = m_creators.find(typeID);

        if(it == m_creators.end())
        {
            std::cout << "could not find type: " << typeID << "\n";
            return NULL;
        }

        BaseCreator* pCreator = (*it).second;
        return pCreator->createGameObject();
    }

private:
    static GameObjectFactory* pInstance;

    std::map<std::string, BaseCreator*> m_creators;
};

typedef GameObjectFactory TheGameObjectFactory;

