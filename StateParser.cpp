#include <cstring>
#include <iostream>
#include "StateParser.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "TextureManager.h"

#include "tinyxml2.h"

bool StateParser::parseState(const char* stateFile, std::string stateID,
    std::vector<GameObject *> *pObjects, std::vector<std::string> *pTextureIDs)
{
    tinyxml2::XMLDocument xmlDoc;

    if(xmlDoc.LoadFile(stateFile))
    {
        std::cout << "xmlDoc error name "
            << xmlDoc.ErrorName() << ", error str: " << xmlDoc.ErrorStr() << "\n";
        return false;
    }

    // get the root element
    tinyxml2::XMLElement* pRoot = xmlDoc.RootElement(); // <STATES>

    // states root node
    tinyxml2::XMLElement* pStateRoot = 0;

    for(
        tinyxml2::XMLElement* e = pRoot->FirstChildElement();
        e != NULL;
        e = e->NextSiblingElement()
    ) {
        if(e->Value() == stateID)
        {
            pStateRoot = e;
            break;
        }
    }

    tinyxml2::XMLElement* pTextureRoot = 0;

    // get the root of the texture elements
    for(
        tinyxml2::XMLElement* e = pStateRoot->FirstChildElement();
        e != NULL;
        e = e->NextSiblingElement()
    ) {
        if(std::strcmp(e->Name(), "TEXTURES") == 0) {
            pTextureRoot = e;
            break;
        }
    }

    parseTextures(pTextureRoot, pTextureIDs);

    // search for objects root node
    tinyxml2::XMLElement* pObjectRoot = 0;

    for(
        tinyxml2::XMLElement* e = pStateRoot->FirstChildElement();
        e != NULL;
        e = e->NextSiblingElement()
    ) {
        if(std::strcmp(e->Name(), "OBJECTS") == 0)
        {
            pObjectRoot = e;
            break;
        }
    }

    // parse the objects
    parseObjects(pObjectRoot, pObjects);

    return true;
}

void StateParser::parseTextures(tinyxml2::XMLElement* pStateRoot,
    std::vector<std::string> *pTextureIDs)
{
    for(
        tinyxml2::XMLElement* e = pStateRoot->FirstChildElement();
        e != NULL;
        e = e->NextSiblingElement()
    ) {
        auto filenameAttribute = e->Attribute("filename");
        auto idAttribute = e->Attribute("ID");
        pTextureIDs->push_back(idAttribute); // push into list

        TheTextureManager::Instance()->load(filenameAttribute,
            idAttribute, TheGame::Instance()->GetRenderer());
    }
}

void StateParser::parseObjects(tinyxml2::XMLElement* pStateRoot,
    std::vector<GameObject *> *pObjects)
{
    for(
        tinyxml2::XMLElement* e = pStateRoot->FirstChildElement();
        e != NULL;
        e = e->NextSiblingElement()
    ) {
        int x, y, width, height, numFrames, callbackID, animSpeed;
        std::string textureID;

        x = e->IntAttribute("x");
        y = e->IntAttribute("y");
        width = e->IntAttribute("width");
        height = e->IntAttribute("height");
        numFrames = e->IntAttribute("numFrames");
        callbackID = e->IntAttribute("callbackID");
        animSpeed = e->IntAttribute("animSpeed");
        textureID = e->Attribute("textureID");

        GameObject* pGameObject = TheGameObjectFactory::Instance()->create(e->Attribute("type"));
        pGameObject->Load(std::unique_ptr<LoaderParams>(new LoaderParams(
            x, y, width, height, numFrames, textureID, callbackID, animSpeed)));
        pObjects->push_back(pGameObject);
    }
}