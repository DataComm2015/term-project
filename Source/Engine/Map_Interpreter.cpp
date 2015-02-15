#include "Map_Interpreter.h"

// Private ifstream tmap_, tset_
inline TiledMap*
Map_Interpreter::create()
{
    TiledMap map = new TiledMap();
    // Read each tile
    readtset(map);
    readtmap(map);
    
    return (map);
}

void Map_Interpreter::readtset(TiledMap& map)
{
    string dummy, texture, tilesize, tile, index;
    float* coords;
    
    getline(tset_, dummy, ':'); // Remove 'texture:'
    getline(tset_, texture); // Extract file path
    fgetc(tset_); // Remove new line
    getline(tset_, dummy, ':'); // Remove 'tilesize:"
    getline(tset_, tilesize); // Extract tilesize
    fgetc(tset_); // Remove new line
    getline(tset_, dummy); // Remove 'tiles:(x,y,w,h)'
    
    while (tset_.good() && tset_.eof() == false)
    {
        getline(tset_, index, ':');
        getline(tset_, tile);
        
        if (tiles.compare(":end"))
        {
            break;
        }
        
        coords = tocords(tile);
        
        map.createTile(index[0], coords[0], coords[1], coords[2], coords[3]);
    }
}

void 
Map_Interpreter::readtmap(TiledMap& map)
{
    string dummy, sid;
    
    getline(tset_, dummy); // Remove 'map'
    
    while (tmap_.good() && tmap_.eof() == false &&
        tmap_ >> id)
    {
        if (id.compare(":end"))
        {
            break;
        }
        map.addTile(id[0]);
    }
}

inline float*
Map_Interpreter::tocords(string& tile)
{
    float[4] coords;
    stringstream ss(tile);
    for (size_t i = 0; i < 4; i++)
    {
        ss >> coords[i];
    }
    
    return coords;
}