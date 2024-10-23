#include <iostream>
#include "LevelParser.h"
#include "base64.h"
#include "TileLayer.h"
#include "Level.h"
#include "Game.h"
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
        if(e->Value() == std::string("layer"))
        {
            parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets());
        }
    }

    std::cout << "levelFile: " << levelFile << ": width: "
        << m_width << ", height: " << m_height << std::endl;

    return pLevel;
}

void LevelParser::parseTilesets(tinyxml2::XMLElement* pTilesetRoot,
    std::vector<Tileset>* pTilesets)
{
    // Add tileset to texture manager
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

    pTilesets->push_back(tileset);
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
        std::cout << "T: " << t << std::endl;
        decodeIDs = base64_decode(t);
        std::cout << "Ids: " << decodeIDs << std::endl;
    }

    std::cout << "DecodeIDS c_str: " << decodeIDs.c_str() << "DecodeIDS size: " << decodeIDs.size() << std::endl;

    // uncompress zlib compression
    uLongf numGids = m_width * m_height * sizeof(int);
    std::vector<unsigned> gids(numGids);
    uncompress((Bytef*) &gids[0], &numGids,
        (const Bytef*)decodeIDs.c_str(), decodeIDs.size());

    std::copy(gids.begin(), gids.end(), std::ostream_iterator<unsigned>(std::cout, ","));

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