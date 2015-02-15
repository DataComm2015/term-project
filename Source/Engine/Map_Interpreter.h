#ifndef MAP_INTERPRETER_H
#define MAP_INTERPRETER_H
#include <iostream>
#include "TiledMap.h"

using namespace std;

class Map_Interpreter
{
private:
    iftream tset_, tmap_;
public:
    explicit Map_Interpreter(string tset, string tmap) : 
    {
        tset_.open(tset, ifstream::in);
        tmap_.open(tmap, ifstream::in);
        if (tset_.good() == false || tmap_.good() == false)
            throw "Map_Interpreter() Exception: Could not open file";
    }
	
	Map_Interpreter() : {}
    
    void setfile(string tset, string tmap) : 
    {
        tset_.open(tset, ifstream::in);
        tmap_.open(tmap, ifstream::in);
        if (tset_.good() == false || tmap_.good() == false)
            throw "Map_Interpreter setfile() Exception: Could not open file";
    }
    
    Tiledmap *create();
    void Map_Interpreter::readtset(TiledMap& map);
    void Map_Interpreter::readtmap(TiledMap& map);
    float* tocord(string& tile);
};

#endif // MAP_INTERPRETER_H