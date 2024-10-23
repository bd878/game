#pragma once

#include <string>
#include <map>
#include <SDL2/SDL.h>

class TextureManager {
public:
    static TextureManager* Instance();

    bool load(std::string filename, std::string id, SDL_Renderer* _renderer);

    void draw(std::string id, int x, int y, int width, int height,
        SDL_Renderer* _renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawFrame(std::string id, int x, int y, int width, int height,
        int currentRow, int currentFrame, SDL_Renderer* _renderer,
        SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawTile(std::string id, int margin, int spacing,
        int x, int y, int width, int height, int currentRow,
        int currentFrame, SDL_Renderer *pRenderer);

    void clearTexture(std::string id);
protected:
    TextureManager() {};
private:
    inline static TextureManager* _instance = nullptr;

    std::map<std::string, SDL_Texture*> m_textures;
};

typedef TextureManager TheTextureManager;
