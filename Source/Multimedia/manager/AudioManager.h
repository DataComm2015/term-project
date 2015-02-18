#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "MusicManager.h"
#include "SoundBufferManager.h"

class AudioManager
{
	public:
		bool loadSound(std::string);
		bool loadMusic(std::string);
		void removeSound(id_resource);
		void removeMusic(id_resource);
		void playSound(id_resource, sf::Vector2f, bool = false);
		void playMusic(id_resource, bool = false);
		void pauseSound(id_resource);
		void pauseMusic(id_resource);
	private:
		MusicManager m_manager;
		SoundBufferManager sb_manager;
		ResourceManager<sf::Sound> s_manager;
};

#endif // AUDIO_MANAGER_H
