#ifndef TILE_MGR_H
#define TILE_MGR_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class TileManager : ResourceManager<sf::FloatRect>
{
public:  
    /**
    * Destructor
    */
    ~TileMgr(){ clear(true); }
    
    /**
    * Loads and populates the map with the contents of the
    * file at path
    *
    * @param std::string path - The path location of the tset file
    * @return sf::FloatRect - returns null, needed for proper overloading 
    */
    sf::FloatRect load(std::string);
    
    /**
    * Uses a string id to get the id_resource to get the rectangle
    *
    * @param std::string id - The string id to be used on the tsetmap.
    * @return sf::FloatRect - Returns the appropriate rectangle
    */
    sf::FloatRect get(std::string);
    
    /**
    * Uses a string id to get the id_resource to remove the rectangle
    *
    * @param std::string id - The string id to be used on the tsetmap.
    * @return sf::FloatRect - The object removed.
    */
    sf::FloatRect remove(std::string);
private:
    /**
    * Map to associate the string id to the id_resource
    */
    map<std::string, id_resource> tsetmap;
    /**
    * The file stream for the tset file.
    */
    ifstream& tset_;
    
    /**
    * Does the actual reading of the file
    *
    * @param void
    * @return void
    */
    void readtset();
    
    /**
    * Trims leading and trailing whitespace from the given string 
    * and returns a copy.
    *
    * @param std::string line - The string to be trimmed
    * @return std::string - The trimmed string
    */
    std::string trim(std::string);
    
    /**
    * Changes the given string to an array of floats.
    *
    * @param std::string tile - The string with the values to be interpreted
    * @return float* - A pointer to the array of rectangle values
    */
    float* tocords(std::string&);
};

#endif // TILE_MGR_H