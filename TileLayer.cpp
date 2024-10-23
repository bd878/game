#include "Game.h"
#include "TextureManager.h"
#include "TileLayer.h"

TileLayer::TileLayer(int tileSize, const std::vector<Tileset> &tilesets)
    : m_tileSize(tileSize), m_tilesets(tilesets), m_position(0,0), m_velocity(0, 0)
{
    m_numColumns = (TheGame::Instance()->GetGameWidth() / m_tileSize);
    m_numRows = (TheGame::Instance()->GetGameHeight() / m_tileSize);
}

void TileLayer::update()
{
    m_position += m_velocity;
}

void TileLayer::render()
{
    int x, y, x2, y2 = 0;

    x = m_position.GetX() / m_tileSize;
    y = m_position.GetY() / m_tileSize;

    x2 = int(m_position.GetX()) % m_tileSize;
    y2 = int(m_position.GetY()) & m_tileSize;

    for(int i = 0; i < m_numRows; i++)
    {
        for(int j = 0; j < m_numColumns; j++)
        {
            int id = m_tileIDs[i][j + x];

            if (id == 0)
            {
                continue;
            }

            Tileset tileset = getTilesetByID(id);

            id--;

            TheTextureManager::Instance()->drawTile(tileset.name, 2, 2,
                (j * m_tileSize) - x2,
                (i * m_tileSize) - y2,
                m_tileSize,
                m_tileSize,
                (id - (tileset.firstGridID - 1)) / tileset.numColumns,
                (id - (tileset.firstGridID - 1)) % tileset.numColumns,
                TheGame::Instance()->GetRenderer()
            );
        }
    }
}