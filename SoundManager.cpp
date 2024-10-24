#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::Instance()
{
  if (s_pInstance == nullptr) {
    s_pInstance = new SoundManager;
  }
  return s_pInstance;
}

SoundManager::SoundManager()
{
    Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
}

SoundManager::~SoundManager()
{
    Mix_CloseAudio();
}

bool SoundManager::load(std::string filename, std::string id, sound_type type)
{
    if(type == SOUND_MUSIC)
    {
        Mix_Music* pMusic = Mix_LoadMUS(filename.c_str());

        if(pMusic == NULL)
        {
            std::cout << "Could not load music: Error - "
                << Mix_GetError() << std::endl;
            return false;
        }

        m_music[id] = pMusic;
        return true;
    }
    else if(type == SOUND_SFX)
    {
        Mix_Chunk* pChunk = Mix_LoadWAV(filename.c_str());
        if(pChunk == NULL)
        {
            std::cout << "Coudl not load SFX: error - "
                << Mix_GetError() << std::endl;

            return false;
        }

        m_sfxs[id] = pChunk;
        return true;
    }
    return false;
}

void SoundManager::playMusic(std::string id, int loop)
{
    Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::playSound(std::string id, int loop)
{
    Mix_PlayChannel(-1, m_sfxs[id], loop);
}