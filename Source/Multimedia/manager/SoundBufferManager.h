#ifndef SOUND_BUFFER_MANAGER_H
#define SOUND_BUFFER_MANAGER_H

#include <SFML/Audio.hpp>
#include "ResourceManager.h"

namespace Manager
{
	/**
	 * Sound Buffer Manager.
	 * 
	 * Loads and stores sound buffer resources.
	 * 
	 * @author Lewis Scott
	 */
	class SoundBuffer : ResourceManager<sf::SoundBuffer*>
	{
		public:
			/**
			* Loads sound from the specified file.
			*
			* @param - std::string path - a qualified path to the desired resource
			* @return - sf::SoundBuffer* - The sound buffer that was loaded
			*/
			static sf::SoundBuffer* load(const std::string);
		
			/**
			* Destructor.
			*/
			~SoundBuffer(){ clear(true); }
		private:
			SoundBuffer(){}
			
			static unsigned int ID_RESOURCE;
			static std::map<id_resource, sf::SoundBuffer*> resource_map;
	};
}

#endif // SOUND_BUFFER_MANAGER_H
