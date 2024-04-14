#pragma once
#include <SDL_mixer.h>
#include <string>
#include <map>

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public:
	static SoundManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new SoundManager(); }
	
	bool Load(std::string ID, std::string soundPath, sound_type type, int volume = MIX_MAX_VOLUME);
	void PlaySound(std::string ID, int loops = 0,int channel = -1);
	void PlayMusic(std::string ID, int loops = 0);
private:
	SoundManager();
	~SoundManager(){}
	std::map<std::string, Mix_Chunk*> m_Sfxs;
	std::map<std::string, Mix_Music*> m_Musics;
	static SoundManager* s_Instance;
};

