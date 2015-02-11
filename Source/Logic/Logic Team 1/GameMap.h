#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include "Cell.h"


/* 
*  The GameMap class contains a list of cells, blocks, and functions
*  for generating a map and placing entities into the map.
*/
class GameMap
{
	public:
		GameMap(Cell **cMap, int w, int h);
		Cell** getCellMap();
		int getWidth();
		int getHeight();

	private:
		Cell** cellMap;
		int width;
		int height;
};

#endif