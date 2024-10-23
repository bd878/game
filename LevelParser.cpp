#include <iostream>
#include "LevelParser.h"
#include "ObjectLayer.h"
#include "base64.h"
#include "TileLayer.h"
#include "Level.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "TextureManager.h"

Level* LevelParser::parseLevel(const char *levelFile)
{
    tinyxml2::XMLDocument levelDocument;
    levelDocument.LoadFile(levelFile);

    Level* pLevel = new Level();

    tinyxml2::XMLElement* pRoot = levelDocument.RootElement();

    pRoot->QueryIntAttribute("tilewidth", &m_tileSize);
    pRoot->QueryIntAttribute("width", &m_width);
    pRoot->QueryIntAttribute("height", &m_height);

    // <properties />
    tinyxml2::XMLElement* pProperties = pRoot->FirstChildElement();

    // parse the textures needed for this level
    for(tinyxml2::XMLElement* e = pProperties->FirstChildElement();
        e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("property"))
        {
            parseTextures(e);
        }
    }

    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != NULL;
        e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            parseTilesets(e, pLevel->getTilesets());
        }
    }

    for(tinyxml2::XMLElement* e = pRoot->FirstChildElement(); e != NULL;
        e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
        {
            if(e->FirstChildElement()->Value() == std::string("object"))
            {
                parseObjectLayer(e, pLevel->getLayers());
            }
            else if (e->FirstChildElement()->Value() == std::string("data"))
            {
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
            }
        }
    }

    return pLevel;
}

void LevelParser::parseTilesets(tinyxml2::XMLElement* pTilesetRoot,
    std::vector<Tileset>* pTilesets)
{
    // Add tileset to texture manager
    std::cout << "adding texture " << pTilesetRoot->FirstChildElement()->Attribute("source") << " with ID " << pTilesetRoot->Attribute("name") << std::endl;
    TheTextureManager::Instance()->load(pTilesetRoot->FirstChildElement()->Attribute("source"),
        pTilesetRoot->Attribute("name"), TheGame::Instance()->GetRenderer());

    // create a tileset object
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->QueryIntAttribute("width",
        &tileset.width);
    pTilesetRoot->FirstChildElement()->QueryIntAttribute("height",
        &tileset.height);
    pTilesetRoot->QueryIntAttribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->QueryIntAttribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->QueryIntAttribute("tileheight", &tileset.tileHeight);
    pTilesetRoot->QueryIntAttribute("spacing", &tileset.spacing);
    pTilesetRoot->QueryIntAttribute("margin", &tileset.margin);
    tileset.name = pTilesetRoot->Attribute("name");


    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);

    std::cout << "Parse tileset " << tileset.name << " "
        << " numColumns: " << tileset.numColumns << std::endl;

    pTilesets->push_back(tileset);
}

void LevelParser::parseTextures(tinyxml2::XMLElement* pTextureRoot)
{
    TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"),
        pTextureRoot->Attribute("name"),
        TheGame::Instance()->GetRenderer());
}

void LevelParser::parseObjectLayer(tinyxml2::XMLElement* pObjectElement,
    std::vector<Layer*> *pLayers)
{
    ObjectLayer* pObjectLayer = new ObjectLayer();

    std::cout << "Layer: " << pObjectElement->FirstChildElement()->Value() << std::endl;

    for(tinyxml2::XMLElement* e = pObjectElement->FirstChildElement();
        e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("object"))
        {
            int x, y, width, height, numFrames, callbackID = 0, animSpeed = 0;
            std::string textureID;
            std::string type;

            // get initial node values type
            e->QueryIntAttribute("x", &x);
            e->QueryIntAttribute("y", &y);

            type = e->Attribute("type");

            std::cout << "Type: " << type << std::endl;

            GameObject* pGameObject = TheGameObjectFactory::Instance()->
                create(e->Attribute("type"));

            // get the property value
            for(tinyxml2::XMLElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
            {
                if(properties->Value() == std::string("properties"))
                {
                    for(tinyxml2::XMLElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
                    {
                        if(property->Value() == std::string("property"))
                        {
                            if(property->Attribute("name") == std::string("numFrames"))
                            {
                                property->QueryIntAttribute("value", &numFrames);
                            }
                            else if(property->Attribute("name") == std::string("textureHeight"))
                            {
                                property->QueryIntAttribute("value", &height);
                            }
                            else if(property->Attribute("name") == std::string("textureID"))
                            {
                                textureID = property->Attribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureWidth"))
                            {
                                property->QueryIntAttribute("value", &width);
                            }
                            else if(property->Attribute("name") == std::string("callbackID"))
                            {
                                property->QueryIntAttribute("value", &callbackID);
                            }
                            else if(property->Attribute("name") == std::string("animSpeed"))
                            {
                                property->QueryIntAttribute("value", &animSpeed);
                            }
                        }
                    }
                }
            }


            std::cout << "x, y, width, height, numFrames, callbackID, animSpeed, textureID " << 
                x << " " << y << " " << width << " " << height << " " << numFrames << " "
                << callbackID << " " << animSpeed << " " << textureID << "\n"; 

            pGameObject->Load(std::unique_ptr<LoaderParams>(new LoaderParams(
                x, y, width, height, numFrames, textureID, callbackID, animSpeed)));
            pObjectLayer->GetGameObjects()->push_back(pGameObject);
        }
    }

    pLayers->push_back(pObjectLayer);
}

void LevelParser::parseTileLayer(tinyxml2::XMLElement* pTileElement,
    std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets)
{
    auto pTileLayer = new TileLayer(m_tileSize, *pTilesets);

    // tile data
    std::vector<std::vector<int>> data;

    std::string decodeIDs;
    tinyxml2::XMLElement* pDataNode;

    for(tinyxml2::XMLElement* e = pTileElement->FirstChildElement(); e != NULL;
        e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
    }

    for(tinyxml2::XMLNode* e = pDataNode->FirstChild(); e != NULL;
        e = e->NextSibling())
    {
        tinyxml2::XMLText* text = e->ToText();
        std::string t = text->Value();
        decodeIDs = base64_decode(t);
    }

    // uncompress zlib compression
    uLongf numGids = m_width * m_height * sizeof(int);
    std::vector<unsigned> gids(numGids);
    uncompress((Bytef*) &gids[0], &numGids,
        (const Bytef*)decodeIDs.c_str(), decodeIDs.size());

    std::vector<int> layerRow(m_width);

    for(int j = 0; j < m_height; j++)
    {
        data.push_back(layerRow);
    }

    for(int rows = 0; rows < m_height; rows++)
    {
        for(int cols = 0; cols < m_width; cols++)
        {
            data[rows][cols] = gids[rows * m_width + cols];
        }
    }

    pTileLayer->setTileIDs(data);

    pLayers->push_back(pTileLayer);
}