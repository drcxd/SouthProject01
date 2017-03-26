#ifndef __AudioManager__
#define __AudioManager__

#include <map>
#include <string>
#include <iostream>

#include <SDL_mixer.h>

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class AudioManager
{
public:

	static AudioManager *Instance()
	{
		if (s_pInstance == 0)
			s_pInstance = new AudioManager();
		return s_pInstance;
	}

	bool load(const std::string fileName, const std::string id, sound_type type);
	void playMusic(const std::string id, int loop);
	void playSound(const std::string id, int loop);
	void stop() const;

private:

	AudioManager() {}
	~AudioManager();

	static AudioManager *s_pInstance;

	std::map<std::string, Mix_Music *> m_music;
	std::map<std::string, Mix_Chunk *> m_sfxs;

};

typedef AudioManager TheAudioManager;
#endif

