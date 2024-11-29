#pragma once

#include <vector>
#include <iostream>
#include "Layer.h"
#include "Player.h"

class LevelParser;
class TileLayer;

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

    std::vector<TileLayer*>* GetCollisionLayers() { return &m_collisionLayers; }

    Player* GetPlayer() { return m_pPlayer; }
    void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

private:

    Player* m_pPlayer;

    std::vector<Tileset> m_tilesets;
    std::vector<Layer*> m_layers;
    std::vector<TileLayer*> m_collisionLayers;
};
