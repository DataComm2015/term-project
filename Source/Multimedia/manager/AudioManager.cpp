#include "AudioManager.h"

bool AudioManager::loadSound(std::string path)
{
	sf::SoundBuffer *sb = sb_manager.load(path);
	if(sb == NULL)
		return false;
	
	resource_id buffer_id = sb_manager.store(sb);
	s_manager.store(sf::Sound(sb_manager.get(buffer_id))), buffer_id); 
	
	return true;
}

bool AudioManager::loadMusic(std::string path)
{
	sf::Music *m = m_manager.load(path);
	if(m == NULL)
		return false;
	
	m_manager.store(m);
	
	return true;
}

void AudioManager::removeSound(id_resource id)
{
	
}

void AudioManager::removeMusic(id_resource id)
{

}

void AudioManager::playSound(id_resource id, sf::Vector2f position, bool restart)
{
	
}

void AudioManager::playMusic(id_resource id, bool restart)
{
	
}

void AudioManager::pauseSound(id_resource id)
{
	
}

void AudioManager::pauseMusic(id_resource id)
{
	
}
