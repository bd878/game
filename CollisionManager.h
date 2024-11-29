#pragma once

#include <vector>
#include "Player.h"
#include "GameObject.h"

class Player;
class GameObject;
class TileLayer;

class CollisionManager
{
public:

    void checkPlayerEnemyBulletCollision(Player* pPlayer);
    void checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects);

    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*> &objects);
    void checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*> &collisionLayers);
};