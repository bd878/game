#pragma once

#include <string>
#include <map>
#include <SDL2/SDL_mixer.h>

enum sound_type
{
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager
{
public:

    static SoundManager* Instance();

    bool load(std::string filename, std::string id, sound_type type);

    void playSound(std::string id, int loop);
    void playMusic(std::string id, int loop);

private:

    inline static SoundManager* s_pInstance = nullptr;

    std::map<std::string, Mix_Chunk*> m_sfxs;
    std::map<std::string, Mix_Music*> m_music;

    SoundManager();
    ~SoundManager();

    SoundManager(const SoundManager&);
    SoundManager &operator=(const SoundManager&);
};

typedef SoundManager TheSoundManager;