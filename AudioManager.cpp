#include "AudioManager.h"

AudioManager::~AudioManager()
{
	for (auto it = m_music.begin(); it != m_music.end(); ++it)
		Mix_FreeMusic(it->second);
	for (auto it = m_sfxs.begin(); it != m_sfxs.end(); ++it)
		Mix_FreeChunk(it->second);
}

bool AudioManager::load(const std::string fileName, const std::string id, sound_type type)
{
	if (type == SOUND_MUSIC)
	{
		Mix_Music *pMusic = Mix_LoadMUS(fileName.c_str());

		if (pMusic == nullptr)
		{
			std::cerr << "Failed when loading music: " << fileName << "\nError: "
				<< Mix_GetError() << std::endl;
			return false;
		}
		m_music[id] = pMusic;
		return true;
	}
	else if (type == SOUND_SFX)
	{
		Mix_Chunk *pChunk = Mix_LoadWAV(fileName.c_str());
		if (pChunk == nullptr)
		{
			std::cerr << "Failed when loading chunk: " << fileName << "\nError: "
				<< Mix_GetError() << std::endl;
			return false;
		}
		m_sfxs[id] = pChunk;
		return true;
	}
	return false;
}

void AudioManager::playMusic(const std::string id, int loop)
{
	Mix_PlayMusic(m_music[id], loop);
}

void AudioManager::playSound(const std::string id, int loop)
{
	Mix_PlayChannel(-1, m_sfxs[id], loop);
}

void AudioManager::stop() const
{
	Mix_HaltMusic();
}

AudioManager *AudioManager::s_pInstance = nullptr;