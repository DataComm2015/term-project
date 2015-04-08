#include "TextureManager.h"

using namespace Manager;

ResourceManager<sf::Texture*> TextureManager::rm;

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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: store
--
-- DATE: February 19, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: id_resource TextureManager::store(sf::Texture* r) 
--
-- RETURNS: id_resource - An unsigned int that can be used to get the stored Texture.
--
-- NOTES:
-- Stores a Texture in the resource manager, returns an id_resource as a handle to it.
----------------------------------------------------------------------------------------------------------------------*/
id_resource TextureManager::store(sf::Texture* r) 
{
	return rm.store(r);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: store
--
-- DATE: February 19, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void TextureManager::store(sf::Texture* r, id_resource id) 
--
-- RETURNS: 
--
-- NOTES:
-- Stores a Texture in the resource manager, replacing the one in the old id slot.
----------------------------------------------------------------------------------------------------------------------*/
void TextureManager::store(sf::Texture* r, id_resource id) 
{
	return rm.store(r, id, true); 
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: get
--
-- DATE: February 19, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: sf::Texture* TextureManager::get(id_resource id) 
--
-- RETURNS: sf::Texture* - The texture with the associated id
--
-- NOTES:
-- Return the texture corresponding to the passed in ID.
----------------------------------------------------------------------------------------------------------------------*/
sf::Texture* TextureManager::get(id_resource id) 
{ 
	return rm.get(id); 
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: remove
--
-- DATE: February 19, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: sf::Texture* TextureManager::remove(id_resource id) 
--
-- RETURNS: sf::Texture* - The texture with the associated id
--
-- NOTES:
-- Removes and returns the Texture corresponding to the given ID.
----------------------------------------------------------------------------------------------------------------------*/
sf::Texture* TextureManager::remove(id_resource id) 
{ 
	return rm.remove(id); 
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: clear
--
-- DATE: February 19, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: unsigned int TextureManager::clear() 
--
-- RETURNS: unsigned int
--
-- NOTES:
-- Clears the held resource manager.
----------------------------------------------------------------------------------------------------------------------*/
unsigned int TextureManager::clear()
{ 
	return rm.clear(true); 
}

