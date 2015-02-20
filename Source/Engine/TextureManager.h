#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

/**
 * Texture Manager.
 * 
 * Loads in a set of tiles from a file and stores them
 * 
 * @author Thomas Tallentire
 */
class TextureManager : public ResourceManager<sf::Texture*>
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
    sf::Texture* load(std::string);
};


#endif
