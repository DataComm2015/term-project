#ifndef TILE_MGR_H
#define TILE_MGR_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class TileMgr
{
private:
    ifstream tset_;
    
public:    
    explicit TileMgr(string path)
    {
        tset_.open(tset.c_str());
        if (tset_.good() == false || tmap_.good() == false)
            throw "Map_Interpreter() Exception: Could not open file";
    }
	
	TileMgr() {}
    
    void load(string path)
    {
        tset_.clear();
        tmap_.clear();
        tset_.open(tset.c_str());
        tmap_.open(tmap.c_str());
        if (tset_.fail() == true || tmap_.fail() == true)
            throw "Map_Interpreter setfile() Exception: Could not open file";
        readtset();
    }
    
    void readtset();
    string trim(string line);
    float* tocords(string& tile);
};

#endif // TILE_MGR_H