#pragma once

#include <vector>

#include "zlib.h"
#include "tinyxml2.h"
#include "Level.h"

class LevelParser
{
public:

    Level* parseLevel(const char* levelFile);

private:

    void parseTilesets(tinyxml2::XMLElement* pTilesetRoot,
        std::vector<Tileset>* pTilesets);

    void parseTileLayer(tinyxml2::XMLElement* pTileElement,
        std::vector<Layer*> *pLayers, const std::vector<Tileset>* pTilesets);

    int m_tileSize;
    int m_width;
    int m_height;
};