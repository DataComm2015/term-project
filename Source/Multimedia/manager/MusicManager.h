#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H

#include <SFML/Audio.hpp>
#include "ResourceManager.h"

/**
 * Music Manager.
 * 
 * Loads and stores music resources.
 * 
 * @author Lewis Scott
 */
class MusicManager : ResourceManager<sf::Music*>
{
	public:
		/**
		* Loads music from the specified file.
		*
		* @param - std::string path - a qualified path to the desired resource
		* @return - sf::Music* - The music that was loaded
		*/
		sf::Music* load(const std::string);
		
		/**
		* Destructor.
		*/
		~MusicManager(){ clear(true); }
};

#endif // MUSIC_MANAGER_H
