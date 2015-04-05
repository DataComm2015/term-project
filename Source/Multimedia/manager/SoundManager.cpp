#include "SoundManager.h"

Manager::ResourceManager<sf::SoundBuffer*> Manager::SoundManager::rm = Manager::ResourceManager<sf::SoundBuffer*>();

sf::SoundBuffer* Manager::SoundManager::load(const std::string path)
{
	sf::SoundBuffer *sb = new sf::SoundBuffer();
	if(sb->loadFromFile(path))
		return sb;
	
	return NULL;
}

sf::Sound Manager::SoundManager::play(id_resource id, sf::Vector2f position)
{
	sf::Sound s(*get(id));
	//s.setRelativeToListener(true);

	s.setPosition(sf::Vector3f(position.x, position.y, 0));
	s.setAttenuation(ATTENUATION);

	s.play();
	return s;
}
