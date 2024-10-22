#include "LevelParser.h"
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