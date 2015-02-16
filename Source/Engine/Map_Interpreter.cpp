#include "Map_Interpreter.h"

// Private ifstream tmap_, tset_
inline TiledMap*
Map_Interpreter::create()
{
    TiledMap *map = new TiledMap();
    readtset(&map);
    readtmap(&map);
    
    return (&map);
}

void Map_Interpreter::readtset(TiledMap& map)
{
    string dummy, texture, tilesize, tile, index;
    float* coords;
    char id;
    
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
        for (string::size_type i = 0; i < index.size(); i++)
        {
            if (!(isspace(index[i])))
            {
                id = index[i];
                break;
            }            
        }
        getline(tset_, tile);
        if (tile.compare("end") == 0)
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
        
        map.addTile(NEW_ROW);
        ss << line;
        while(!ss.eof())
        {
            ss >> id;
            map.addTile(id[0]);
        }
    }
}

inline float*
Map_Interpreter::tocords(string& tile)
{
    float coords[4];
    stringstream ss(tile);
    for (size_t i = 0; i < 4; i++)
    {
        ss >> coords[i];
    }
    
    return coords;
}

int main()
{
    Map_Interpreter *mi = new Map_Interpreter();
    TiledMap *map;
    try {
        mi->setfile("tset.txt", "tmap.txt");
    } catch (const char *e)
    {
        cout << "Exception: " << e <<  endl;
        return(1);
    }
    map = mi->create();
    delete(mi);
    return 0;
}