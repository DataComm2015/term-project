#include "SoundBufferManager.h"

sf::SoundBuffer* SoundBufferManager::load(const std::string path)
{
	sf::SoundBuffer *sb = new sf::SoundBuffer();
	if(sb->loadFromFile(path))
		return sb;
	
	return NULL;
}
