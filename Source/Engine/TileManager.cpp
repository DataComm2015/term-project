#include "TileManager.h"

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
-- RETURNS: sf::FloatRect - Returns null, needed for proper overloading 
--
-- NOTES:
-- Loads and populates the map with the contents of the
-- file at path
----------------------------------------------------------------------------------------------------------------------*/
sf::FloatRect 
TileManager::load(std::string path)
{
    tset_.clear();
    tset_.open(tset.c_str());
    if (tset_.fail() == true || tmap_.fail() == true)
        throw "Map_Interpreter setfile() Exception: Could not open file";
    readtset();
    return NULL;
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
sf::FloatRect 
TileManager::get(std::string rectId)
{
    return get(tsetmap[rectId]);
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
sf::FloatRect 
TileManager::remove(std::string rectId)
{
    sf::FloatRect rect = remove(tsetmap[rectId]);
    tsetmap.erase(rectId)
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
-- RETURNS: void
--
-- NOTES:
-- Does the actual reading of the file.
----------------------------------------------------------------------------------------------------------------------*/
void 
TileManager::readtset()
{
    std::string dummy, texture, tilesize, tile, index;
    std::string id;
    float* coords;
    Tile tile;
    id_resource value;
    
    std::getline(tset_, dummy, ':'); // Remove 'texture:'
    std::getline(tset_, texture); // Extract file path
    std::getline(tset_, dummy); // Remove new line
    std::getline(tset_, dummy, ':'); // Remove 'tilesize:"
    std::getline(tset_, tilesize); // Extract tilesize
    std::getline(tset_, dummy); // Remove new line
    std::getline(tset_, dummy); // Remove 'tiles:(x,y,w,h)'
    
    while (tset_.good() && tset_.eof() == false)
    {
        std::getline(tset_, index, ':');
        id = trim(index);
        
        std::getline(tset_, tile);
        if (tile.compare("end") == 0)
        {
            break;
        }
        
        coords = tocords(tile);
        value = store(new sf::FloatRect(coords[0], coords[1], coords[2], coords[3]);
        tsetmap[id] = value;
    }
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
    string id = "";
    for (std::string::size_type i = 0; i < index.size(); i++)
    {
        if (!(isspace(line[i])))
        {
            id += index[i];
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
-- INTERFACE: float* TileManager::tocords(std::string& tile)
--
-- RETURNS: float* - A pointer to the array of rectangle values
--
-- NOTES:
-- Changes the given string to an array of floats.
----------------------------------------------------------------------------------------------------------------------*/
float*
TileManager::tocords(std::string& tile)
{
    float coords[4];
    std::stringstream ss(tile);
    for (size_t i = 0; i < 4; i++)
    {
        ss >> coords[i];
    }
    
    return coords;
}


