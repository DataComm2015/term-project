#include "MusicManager.h"

#include "SoundManager.h"

Manager::ResourceManager<sf::Music*> Manager::MusicManager::rm = Manager::ResourceManager<sf::Music*>();

/**
* Loads a file for use with the music manager
*
* @date         2015-02-26
*
* @revisions	
*
* @designer     Lewis Scott
*
* @programmer   Lewis Scott
*
* @return       sf::Music *
*/
sf::Music* Manager::MusicManager::load(const std::string path)
{
    if (Manager::SoundManager::disabled)
        return NULL;

	sf::Music *m = new sf::Music;
	if(m->openFromFile(path))
		return m;
	
	return NULL;
}
