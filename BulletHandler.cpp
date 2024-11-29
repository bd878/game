#include "Game.h"
#include "BulletHandler.h"
#include "LoaderParams.h"

BulletHandler* BulletHandler::s_pInstance = new BulletHandler();

BulletHandler::BulletHandler()
{
}

void BulletHandler::AddPlayerBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading)
{
    PlayerBullet* pPlayerBullet = new PlayerBullet();
    pPlayerBullet->Load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, numFrames, textureID)), heading);
    
    m_playerBullets.push_back(pPlayerBullet);
}

void BulletHandler::AddEnemyBullet(int x, int y, int width, int height, std::string textureID, int numFrames, Vector2D heading)
{
    EnemyBullet* pEnemyBullet = new EnemyBullet();
    pEnemyBullet->Load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, numFrames, textureID)), heading);
    
    m_enemyBullets.push_back(pEnemyBullet);
}

void BulletHandler::ClearBullets()
{
    m_enemyBullets.clear();
    m_playerBullets.clear();
}

void BulletHandler::UpdateBullets()
{
    for (std::vector<PlayerBullet*>::iterator p_it = m_playerBullets.begin(); p_it != m_playerBullets.end();)
    {
        if((*p_it)->GetPosition().GetX() < 0 || (*p_it)->GetPosition().GetX() > TheGame::Instance()->GetGameWidth()
           || (*p_it)->GetPosition().GetY() < 0 || (*p_it)->GetPosition().GetY() > TheGame::Instance()->GetGameHeight() || (*p_it)->Dead())
        {
            delete * p_it;
            p_it = m_playerBullets.erase(p_it);
        }
        else
        {
            (*p_it)->Update();
            ++p_it;
        }
    }
    
    for (std::vector<EnemyBullet*>::iterator e_it = m_enemyBullets.begin(); e_it != m_enemyBullets.end();)
    {
        if((*e_it)->GetPosition().GetX() < 0 || (*e_it)->GetPosition().GetX() > TheGame::Instance()->GetGameWidth()
           || (*e_it)->GetPosition().GetY() < 0 || (*e_it)->GetPosition().GetY() > TheGame::Instance()->GetGameHeight() || (*e_it)->Dead())
        {
            delete * e_it;
            e_it = m_enemyBullets.erase(e_it);
        }
        else
        {
            (*e_it)->Update();
            ++e_it;
        }
    }
}

void BulletHandler::DrawBullets()
{
    for (int p = 0; p < m_playerBullets.size(); p++)
    {
        m_playerBullets[p]->Draw();
    }
    
    for (int e = 0; e < m_enemyBullets.size(); e++)
    {
        m_enemyBullets[e]->Draw();
    }
}