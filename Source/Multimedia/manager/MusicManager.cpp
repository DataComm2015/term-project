#include "MusicManager.h"

sf::Music* Manager::Music::load(const std::string path)
{
	sf::Music *m = new sf::Music;
	if(m->openFromFile(path))
		return m;
	
	return NULL;
}
