#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "TextureManager.h"

TextureManager* TextureManager::Instance()
{
    if (_instance == nullptr) {
        _instance = new TextureManager;
    }
    return _instance;
}

bool TextureManager::load(std::string filename, std::string id, SDL_Renderer* _renderer)
{
    SDL_Surface* pTempSurface = IMG_Load(filename.c_str());
    if (pTempSurface == 0)
    {
         return false;
    }

    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(_renderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    int w, h;
    if (SDL_QueryTexture(pTexture, NULL, NULL, &w, &h) < 0) {
         return false;
    }

    if (pTexture != 0)
    {
        m_textures[id] = pTexture;
        return true;
    }

    return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height,
    SDL_Renderer* _renderer, SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect dstRect;

  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = dstRect.w = width;
  srcRect.h = dstRect.h = height;
  dstRect.x = x;
  dstRect.y = y;

  SDL_RenderCopyEx(_renderer, m_textures[id], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height,
    int currentRow, int currentFrame, SDL_Renderer* _renderer, SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect dstRect;

  srcRect.x = width * currentFrame;
  srcRect.y = height * currentRow;
  srcRect.w = dstRect.w = width;
  srcRect.h = dstRect.h = height;
  dstRect.x = x;
  dstRect.y = y;

  SDL_RenderCopyEx(_renderer, m_textures[id], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing,
    int x, int y, int width, int height, int currentRow,
    int currentFrame, SDL_Renderer *pRenderer)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;

    SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect,
        &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::clearTexture(std::string id)
{
    m_textures.erase(id);
}