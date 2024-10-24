#pragma once

#include <vector>
#include <iostream>
#include "Layer.h"

class LevelParser;

struct Tileset
{
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    std::string name;
};

class Level
{
public:

    friend class LevelParser;

    Level() {};
    ~Level();

    void update();
    void render();

    std::vector<Tileset>* getTilesets()
    {
        return &m_tilesets;
    }

    std::vector<Layer*>* getLayers()
    {
        return &m_layers;
    }

private:

    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;
};
