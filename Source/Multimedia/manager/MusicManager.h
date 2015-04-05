#ifndef MUSIC_MANAGER_H
#define MUSIC_MANAGER_H

#include <SFML/Audio.hpp>
#include "ResourceManager.h"

namespace Manager
{
	/**
	 * Music Manager.
	 * 
	 * Loads and stores music resources.
	 * 
	 * @author Lewis Scott
	 */
	class MusicManager
	{
		public:
			static ResourceManager<sf::Music*> rm;
			/**
			* Loads music from the specified file.
			*
			* @param - std::string path - a qualified path to the desired resource
			* @return - sf::Music* - The music that was loaded
			*/
			static sf::Music* load(const std::string);
		
			/**
			* Wrapper functions
			*/
			static id_resource store(sf::Music* m){ return rm.store(m); }
			static void store(sf::Music* m, id_resource id){ rm.store(m, id, true); }
			static sf::Music* get(id_resource id){ return rm.get(id); }
			static sf::Music* remove(id_resource id){ return rm.remove(id); }
			static unsigned int clear(){ return rm.clear(true); }
		
			/**
			* Destructor.
			*/
			~MusicManager(){ clear(); }
		
		private:
			/**
			* Private constructor (static class)
			*/
			MusicManager(){}


	};
}

#endif // MUSIC_MANAGER_H
