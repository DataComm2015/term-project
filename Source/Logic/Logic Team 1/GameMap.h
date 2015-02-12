#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include "Cell.h"
#include "Block.h"


/* 
*	The GameMap class contains a list of cells, blocks, and functions
*	for generating a map and placing entities into the map.
*/
class GameMap
{
	public:
		GameMap(Cell **cMap, int w, int h);
		~GameMap();
		bool generateMap();
		bool createBlockMap();
		void generateZones();

		Cell** getCellMap();
		Block** getBlockMap();
		int getWidth();
		int getHeight();
		int getBlocksHor();
		int getBlocksVert();

	private:
		Cell** cellMap;
		Block** blockMap;
		int width;
		int height;
		int bWidth;
		int bHeight;
};

#endif