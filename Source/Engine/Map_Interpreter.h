#ifndef MAP_INTERPRETER_H
#define MAP_INTERPRETER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include "TiledMap.h"

using namespace std;

class Map_Interpreter
{
private:
    ifstream tset_, tmap_;
    
public:
    explicit Map_Interpreter(string tset, string tmap)
    {
        tset_.open(tset.c_str());
        tmap_.open(tmap.c_str());
        if (tset_.good() == false || tmap_.good() == false)
            throw "Map_Interpreter() Exception: Could not open file";
    }
	
	Map_Interpreter() {}
    
    void setfile(string tset, string tmap)
    {
        tset_.clear();
        tmap_.clear();
        tset_.open(tset.c_str());
        tmap_.open(tmap.c_str());
        if (tset_.fail() == true || tmap_.fail() == true)
            throw "Map_Interpreter setfile() Exception: Could not open file";
    }
    
    TiledMap* create();
    void readtset(TiledMap& map);
    void readtmap(TiledMap& map);
    float* tocords(string& tile);
};

#endif // MAP_INTERPRETER_H