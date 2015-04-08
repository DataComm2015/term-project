#include "TileManager.h"


using namespace Manager;

ResourceManager<sf::FloatRect*> TileManager::rm;

std::map<std::string, id_resource> TileManager::tsetmap_;

std::map<id_resource, std::set<std::string> > TileManager::texturemap_;

std::ifstream TileManager::tset_;


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: load
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: sf::FloatRect TileManager::load(std::string path)
--
-- RETURNS: id_resource - Texture id with the tileset
--
-- NOTES:
-- Loads and populates the map with the contents of the
-- file at path
----------------------------------------------------------------------------------------------------------------------*/
id_resource
TileManager::load(std::string path)
{
    tset_.clear();
    tset_.open(path.c_str());
    if (tset_.fail() == true)
        throw "Map_Interpreter setfile() Exception: Could not open file";
    return readtset();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: get
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: sf::FloatRect TileManager::get(std::string rectId)
--
-- RETURNS: sf::FloatRect - Returns the appropriate rectangle
--
-- NOTES:
-- Uses a string id to get the id_resource to get the rectangle
----------------------------------------------------------------------------------------------------------------------*/
sf::FloatRect* 
TileManager::get(std::string rectId)
{
    return get(tsetmap_[rectId]);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: remove
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: sf::FloatRect TileManager::remove(std::string rectId)
--
-- RETURNS: void
--
-- NOTES:
-- Uses a string id to get the id_resource to remove the rectangle
----------------------------------------------------------------------------------------------------------------------*/
sf::FloatRect* 
TileManager::remove(std::string rectId)
{
    sf::FloatRect *rect = remove(tsetmap_[rectId]);
    tsetmap_.erase(rectId);
    return (rect);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: readtset
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void TileManager::readtset()
--
-- RETURNS: id_resource - Texture id with the tileset
--
-- NOTES:
-- Does the actual reading of the file.
----------------------------------------------------------------------------------------------------------------------*/
id_resource 
TileManager::readtset()
{
    std::string dummy, texture, tilesize, tile, index;
    std::string id;
    std::set<std::string> tile_ids;
    float coords[4];
    id_resource value, texture_id;
    
    std::getline(tset_, dummy, ':'); // Remove 'texture:'
    std::getline(tset_, texture); // Extract file path
    std::getline(tset_, dummy); // Remove new line
    std::getline(tset_, dummy, ':'); // Remove 'tilesize:"
    std::getline(tset_, tilesize); // Extract tilesize
    std::getline(tset_, dummy); // Remove new line
    std::getline(tset_, dummy); // Remove 'tiles:(x,y,w,h)'
    
    texture_id = Manager::TextureManager::store(Manager::TextureManager::load(texture));
    while (tset_.good() && tset_.eof() == false)
    {
        std::getline(tset_, index, ':');
        id = trim(index);
        
        std::getline(tset_, tile);
        if (tile.compare("end") == 0)
        {
            break;
        }
        
        tocords(tile, coords);
        value = store(new sf::FloatRect(coords[0], coords[1], coords[2], coords[3]));
        tsetmap_[id] = value;
        tile_ids.insert(id);
    }
    texturemap_[texture_id] = tile_ids;
    return texture_id;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: trim
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: std::string TileManager::trim(std::string line)
--
-- RETURNS: std::string - The trimmed string
--
-- NOTES:
-- Trims leading and trailing whitespace from the given string 
-- and returns a copy.
----------------------------------------------------------------------------------------------------------------------*/
std::string
TileManager::trim(std::string line)
{
    std::string id = "";
    for (std::string::size_type i = 0; i < line.size(); i++)
    {
        if (!(isspace(line[i])))
        {
            id += line[i];
            break;
        }            
    }
    return id;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: tocords
--
-- DATE: February 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void TileManager::tocords(std::string& tile, float *coords)
--
-- RETURNS: void
--
-- NOTES:
-- Changes the given string to an array of floats.
----------------------------------------------------------------------------------------------------------------------*/
void
TileManager::tocords(std::string& tile, float *coords)
{
    std::stringstream ss(tile);
    for (size_t i = 0; i < 4; i++)
    {
        ss >> coords[i];
    }
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
-- INTERFACE: id_resource TileManager::store(sf::Texture* r) 
--
-- RETURNS: id_resource - An unsigned int that can be used to get the stored Texture.
--
-- NOTES:
-- Stores a Tile in the resource manager, returns an id_resource as a handle to it.
----------------------------------------------------------------------------------------------------------------------*/
id_resource TileManager::store(sf::FloatRect* r) 
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
-- INTERFACE: void TileManager::store(sf::Texture* r, id_resource id) 
--
-- RETURNS: 
--
-- NOTES:
-- Stores a Tile in the resource manager, replacing the one in the old id slot.
----------------------------------------------------------------------------------------------------------------------*/
void TileManager::store(sf::FloatRect* r, id_resource id) 
{ 
	rm.store(r, id, true); 
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
-- INTERFACE: sf::Texture* TileManager::get(id_resource id) 
--
-- RETURNS: sf::Texture* - The Tile with the associated id
--
-- NOTES:
-- Return the Tile corresponding to the passed in ID.
----------------------------------------------------------------------------------------------------------------------*/
sf::FloatRect* TileManager::get(id_resource id) 
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
-- INTERFACE: sf::Texture* TileManager::remove(id_resource id) 
--
-- RETURNS: sf::Texture* - The Tile with the associated id
--
-- NOTES:
-- Removes and returns the Tile corresponding to the given ID.
----------------------------------------------------------------------------------------------------------------------*/
sf::FloatRect* TileManager::remove(id_resource id) 
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
-- INTERFACE: unsigned int TileManager::clear() 
--
-- RETURNS: unsigned int
--
-- NOTES:
-- Clears the held resource manager.
----------------------------------------------------------------------------------------------------------------------*/
unsigned int TileManager::clear() 
{
	return rm.clear(true); 
}

