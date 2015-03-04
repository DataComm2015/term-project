#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SFML/Graphics.hpp>
#include "../Multimedia/manager/ResourceManager.h"

typedef unsigned int id_resource;

/**
 * Texture Manager.
 * 
 * Loads in a set of tiles from a file and stores them
 * 
 * @author Thomas Tallentire
 */
namespace Manager
{
    class TextureManager
        {
        public: 
            /**
            * Destructor
            */
            ~TextureManager(){ clear(); }

            /**
            * Loads a texture from the given address Throws a const char* exception if 
            * it fails to load.
            *
            * @param std::string path - The path location of the tset file
            * @return sf::Texture - Texture loaded from path
            */
            static sf::Texture* load(std::string);
            
            /**
            * Static versions of the Resource Manager functions.
            */
            static id_resource store(sf::Texture* r);
            static void store(sf::Texture* r, id_resource id);
            static sf::Texture* get(id_resource id);
            static sf::Texture* remove(id_resource id);
            static unsigned int clear();
            
        private:
            static ResourceManager<sf::Texture*> rm;
        };
}

#endif
