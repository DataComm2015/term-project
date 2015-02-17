#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H

#include <SFML/Audio.hpp>
#include "ResourceManager.h"

class MusicManager : ResourceManager<sf::Music*>
{
	public:
		sf::Music* load(const std::string);
};

#endif // MUSIC_MANAGER_H
