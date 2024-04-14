#include "SoundManager.h"
#include <iostream>
SoundManager* SoundManager::s_Instance = NULL;

SoundManager::SoundManager() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    // Cấp phát 32 kênh
    Mix_AllocateChannels(32);

}

bool SoundManager::Load(std::string id, std::string path, sound_type type,int volume) {
    if (type == SOUND_SFX) {
        Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
        
        if (chunk == nullptr) {
            std::cout << "loi khong load sfx duoc";
            return false;
        }
        Mix_VolumeChunk(chunk, volume);
        m_Sfxs[id] = chunk;
    }
    else if (type == SOUND_MUSIC) {
        Mix_Music* music = Mix_LoadMUS(path.c_str());
        if (music == nullptr) {
            std::cout << "loi khong load music duoc";
            return false;
        }
        Mix_VolumeMusic(volume);
        m_Musics[id] = music;
    }
    return true;
}

void SoundManager::PlaySound(std::string id, int loops,int channel) {
    Mix_PlayChannel(channel, m_Sfxs[id], loops);
}

void SoundManager::PlayMusic(std::string id, int loops) {
    Mix_PlayMusic(m_Musics[id], loops);
}