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
	class SoundBuffer
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
			* Wrapper functions
			*/
			static id_resource store(sf::SoundBuffer* sb){ return rm.store(sb); }
			static void store(sf::SoundBuffer* sb, id_resource id){ rm.store(sb, id, true); }
			static sf::SoundBuffer* get(id_resource id){ return rm.get(id); }
			static sf::SoundBuffer* remove(id_resource id){ return rm.remove(id); }
			static unsigned int clear(){ return rm.clear(true); }
		
			/**
			* Destructor.
			*/
			~SoundBuffer(){ clear(); }
		private:
			/**
			* Private constructor (static class)
			*/
			SoundBuffer(){}
			
			static ResourceManager<sf::SoundBuffer*> rm;
	};
}

#endif // SOUND_BUFFER_MANAGER_H
