#pragma once

#include <iostream>
#include <vector>
#include "PlayerBullet.h"
#include "EnemyBullet.h"

class BulletHandler
{
public:

    static BulletHandler* Instance()
    {
        if (s_pInstance == nullptr)
        {
            s_pInstance = new BulletHandler();
            return s_pInstance;
        }
        return s_pInstance;
    }

    void AddPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);
    void AddEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading);

    void UpdateBullets();
    void DrawBullets();

    void ClearBullets();

    const std::vector<PlayerBullet*> GetPlayerBullets() { return m_playerBullets; }
    const std::vector<EnemyBullet*> GetEnemyBullets() { return m_enemyBullets; }

private:

    BulletHandler();
    ~BulletHandler();

    BulletHandler(const BulletHandler&);
    BulletHandler& operator=(const BulletHandler&);

    static BulletHandler* s_pInstance;

    std::vector<PlayerBullet*> m_playerBullets;
    std::vector<EnemyBullet*> m_enemyBullets;
};

typedef BulletHandler TheBulletHandler;