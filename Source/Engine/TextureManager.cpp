#include "TextureManager.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: load
--
-- DATE: February 19, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: sf::Texture TextureManager::load(std::string path)
--
-- RETURNS: sf::Texture - the texture extracted from the file. 
--
-- NOTES:
-- Loads a texture from the given address. Throws a const char* exception if 
-- it fails to load.
----------------------------------------------------------------------------------------------------------------------*/
sf::Texture* 
TextureManager::load(std::string path)
{
    sf::Texture *texture = new sf::Texture();
    
    if (texture->loadFromFile(path) == false)
    {
         throw("TextureManager::load : Texture could not be loaded");
    }
    return (texture);
}
