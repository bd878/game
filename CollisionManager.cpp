#include "CollisionManager.h"
#include "Collisions.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletHandler.h"
#include "TileLayer.h"

void CollisionManager::checkPlayerEnemyBulletCollision(Player* pPlayer)
{
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = pPlayer->GetPosition().GetX();
    pRect1->y = pPlayer->GetPosition().GetY();
    pRect1->w = pPlayer->GetWidth();
    pRect1->h = pPlayer->GetHeight();
    
    for(int i = 0; i < TheBulletHandler::Instance()->GetEnemyBullets().size(); i++)
    {
        EnemyBullet* pEnemyBullet = TheBulletHandler::Instance()->GetEnemyBullets()[i];
        
        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = pEnemyBullet->GetPosition().GetX();
        pRect2->y = pEnemyBullet->GetPosition().GetY();
        
        pRect2->w = pEnemyBullet->GetWidth();
        pRect2->h = pEnemyBullet->GetHeight();
        
        if(RectRect(pRect1, pRect2))
        {
            if(!pPlayer->Dying() && !pEnemyBullet->Dying())
            {
                pEnemyBullet->Collision();
                pPlayer->Collision();
            }
        }
        
        delete pRect2;
    }
    
    delete pRect1;
}

void CollisionManager::checkEnemyPlayerBulletCollision(const std::vector<GameObject *> &objects)
{
    for(int i = 0; i < objects.size(); i++)
    {
        GameObject* pObject = objects[i];
        
        for(int j = 0; j < TheBulletHandler::Instance()->GetPlayerBullets().size(); j++)
        {
            if(pObject->Type() != std::string("Enemy") || !pObject->Updating())
            {
                continue;
            }
            
            SDL_Rect* pRect1 = new SDL_Rect();
            pRect1->x = pObject->GetPosition().GetX();
            pRect1->y = pObject->GetPosition().GetY();
            pRect1->w = pObject->GetWidth();
            pRect1->h = pObject->GetHeight();
            
            PlayerBullet* pPlayerBullet = TheBulletHandler::Instance()->GetPlayerBullets()[j];
            
            SDL_Rect* pRect2 = new SDL_Rect();
            pRect2->x = pPlayerBullet->GetPosition().GetX();
            pRect2->y = pPlayerBullet->GetPosition().GetY();
            pRect2->w = pPlayerBullet->GetWidth();
            pRect2->h = pPlayerBullet->GetHeight();
            
            if(RectRect(pRect1, pRect2))
            {
                if(!pObject->Dying() && !pPlayerBullet->Dying())
                {
                    pPlayerBullet->Collision();
                    pObject->Collision();
                }
                
            }
            
            delete pRect1;
            delete pRect2;
        }
    }
}

void CollisionManager::checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects)
{
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = pPlayer->GetPosition().GetX();
    pRect1->y = pPlayer->GetPosition().GetY();
    pRect1->w = pPlayer->GetWidth();
    pRect1->h = pPlayer->GetHeight();
    
    for(int i = 0; i < objects.size(); i++)
    {
        if(objects[i]->Type() != std::string("Enemy") || !objects[i]->Updating())
        {
            continue;
        }
        
        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = objects[i]->GetPosition().GetX();
        pRect2->y = objects[i]->GetPosition().GetY();
        pRect2->w = objects[i]->GetWidth();
        pRect2->h = objects[i]->GetHeight();
        
        if(RectRect(pRect1, pRect2))
        {
            if(!objects[i]->Dead() && !objects[i]->Dying())
            {
                pPlayer->Collision();
            }
        }
        
        delete pRect2;
    }
    
    delete pRect1;
}

void CollisionManager::checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer*>& collisionLayers)
{
    for(std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); it != collisionLayers.end(); ++it)
    {
        TileLayer* pTileLayer = (*it);
        std::vector<std::vector<int>> tiles = pTileLayer->GetTileIDs();
        
        Vector2D layerPos = pTileLayer->GetPosition();
        
        int x, y, tileColumn, tileRow, tileid = 0;
        
        x = layerPos.GetX() / pTileLayer->GetTileSize();
        y = layerPos.GetY() / pTileLayer->GetTileSize();
        
        if(pPlayer->GetVelocity().GetX() >= 0 || pPlayer->GetVelocity().GetY() >= 0)
        {
            tileColumn = ((pPlayer->GetPosition().GetX() + pPlayer->GetWidth()) / pTileLayer->GetTileSize());
            tileRow = ((pPlayer->GetPosition().GetY() + pPlayer->GetHeight()) / pTileLayer->GetTileSize());
            tileid = tiles[tileRow + y][tileColumn + x];
        }
        else if(pPlayer->GetVelocity().GetX() < 0 || pPlayer->GetVelocity().GetY() < 0)
        {
            tileColumn = pPlayer->GetPosition().GetX() / pTileLayer->GetTileSize();
            tileRow = pPlayer->GetPosition().GetY() / pTileLayer->GetTileSize();
            tileid = tiles[tileRow + y][tileColumn + x];
        }
        
        if(tileid != 0)
        {
            pPlayer->Collision();
        }
    }
}