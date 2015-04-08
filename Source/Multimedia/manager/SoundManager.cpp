#include "SoundManager.h"

Manager::ResourceManager<sf::SoundBuffer*> Manager::SoundManager::rm = Manager::ResourceManager<sf::SoundBuffer*>();
bool Manager::SoundManager::disabled = false;


sf::SoundBuffer* Manager::SoundManager::load(const std::string path)
{
    if (Manager::SoundManager::disabled)
        return NULL;

	sf::SoundBuffer *sb = new sf::SoundBuffer();
	if(sb->loadFromFile(path))
		return sb;

	return NULL;
}

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
