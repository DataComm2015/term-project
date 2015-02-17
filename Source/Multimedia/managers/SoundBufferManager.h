#ifndef SOUND_BUFFER_MANAGER_H
#define SOUND_BUFFER_MANAGER_H

#include <SFML/Audio.hpp>
#include "ResourceManager.h"

/**
 * Sound Buffer Manager.
 * 
 * Loads and stores sound buffer resources.
 * 
 * @author Lewis Scott
 */
class SoundBufferManager : ResourceManager<sf::SoundBuffer*>
{
	public:
		/**
		* Loads sound from the specified file.
		*
		* @param - std::string path - a qualified path to the desired resource
		* @return - sf::SoundBuffer* - The sound buffer that was loaded
		*/
		sf::SoundBuffer* load(const std::string);
};

#endif // SOUND_BUFFER_MANAGER_H
