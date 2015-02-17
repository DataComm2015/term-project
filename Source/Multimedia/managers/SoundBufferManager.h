#ifndef SOUND_BUFFER_MANAGER_H
#define SOUND_BUFFER_MANAGER_H

#include <SFML/Audio.hpp>
#include "ResourceManager.h"

class SoundBufferManager : ResourceManager<sf::SoundBuffer*>
{
	public:
		sf::SoundBuffer* load(const std::string);
};

#endif // SOUND_BUFFER_MANAGER_H
