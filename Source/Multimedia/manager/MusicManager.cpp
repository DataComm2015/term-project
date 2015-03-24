#include "MusicManager.h"

Manager::ResourceManager<sf::Music*> Manager::MusicManager::rm = Manager::ResourceManager<sf::Music*>();

sf::Music* Manager::MusicManager::load(const std::string path)
{
	sf::Music *m = new sf::Music;
	if(m->openFromFile(path))
		return m;
	
	return NULL;
}
