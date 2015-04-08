#include "SoundManager.h"

Manager::ResourceManager<sf::SoundBuffer*> Manager::SoundManager::rm = Manager::ResourceManager<sf::SoundBuffer*>();
bool Manager::SoundManager::disabled = false;

/**
* Loads a sound buffer for use with the sound manager
*
* @date         2015-02-26
*
* @revisions	
*
* @designer     Lewis Scott
*
* @programmer   Lewis Scott
*
* @return       sf::SoundBuffer *
*/
sf::SoundBuffer* Manager::SoundManager::load(const std::string path)
{
    if (Manager::SoundManager::disabled)
        return NULL;

	sf::SoundBuffer *sb = new sf::SoundBuffer();
	if(sb->loadFromFile(path))
		return sb;

	return NULL;
}

/**
* Creates a sound object bound the the relevant sound buffer in the manager
*
* @date         2015-02-26
*
* @revisions	
*
* @designer     Lewis Scott
*
* @programmer   Lewis Scott
*
* @return       sf::Sound
*/
sf::Sound Manager::SoundManager::play(id_resource id, sf::Vector2f position)
{
    if (Manager::SoundManager::disabled)
        return sf::Sound();

	sf::Sound s(*get(id));
	//s.setRelativeToListener(true);

	s.setPosition(sf::Vector3f(position.x, position.y, 0));
	s.setAttenuation(ATTENUATION);

	return s;
}
