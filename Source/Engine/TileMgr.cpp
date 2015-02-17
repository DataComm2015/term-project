#include "TileMgr.h"

void TileMgr::
readtset()
{
    string dummy, texture, tilesize, tile, index;
    float* coords;
    string id;
    Tile tile;
    
    getline(tset_, dummy, ':'); // Remove 'texture:'
    getline(tset_, texture); // Extract file path
    getline(tset_, dummy); // Remove new line
    getline(tset_, dummy, ':'); // Remove 'tilesize:"
    getline(tset_, tilesize); // Extract tilesize
    getline(tset_, dummy); // Remove new line
    getline(tset_, dummy); // Remove 'tiles:(x,y,w,h)'
    
    while (tset_.good() && tset_.eof() == false)
    {
        getline(tset_, index, ':');
        id = trim(index);
        
        getline(tset_, tile);
        if (tile.compare("end") == 0)
        {
            break;
        }
        
        coords = tocords(tile);
        tileset[id] = new sf::FloatRect(coords[0], coords[1], coords[2], coords[3]);;
    }
}

string
TileMgr::trim(string line)
{
    string id = "";
    for (string::size_type i = 0; i < index.size(); i++)
    {
        if (!(isspace(line[i])))
        {
            id += index[i];
            break;
        }            
    }
    return id;
}

/*void 
TileMgr::readtmap(TiledMap& map)
{
    string dummy, line, id;
    stringstream ss;
    getline(tmap_, dummy); // Remove 'map'
    
    while (tmap_.good() && tmap_.eof() == false)
    {
        getline(tmap_, line);
        
        if (id.compare(":end") == 0)
        {
            break;
        }
        
        map.addTile(NEXT_ROW);
        ss << line;
        while(!ss.eof())
        {
            ss >> id;
            if (id[0] == '0')
                map.addTile(NEXT_COL);
            map.addTile(id[0]);
        }
    }
}*/

inline float*
TileMgr::tocords(string& tile)
{
    float coords[4];
    stringstream ss(tile);
    for (size_t i = 0; i < 4; i++)
    {
        ss >> coords[i];
    }
    
    return coords;
}
