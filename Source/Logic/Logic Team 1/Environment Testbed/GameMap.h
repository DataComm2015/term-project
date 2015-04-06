#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include "Cell.h"
#include "Block.h"


/* The number of human players in a round */
#define NUM_PLAYERS 4

/* The percent of enemy grass zone blocks */
#define MAX_GRASS_ENEMIES 45

/* The percent of of enemy stone zone blocks */
#define MAX_STONE_ENEMIES 30

/* The percent of structure grass zone blocks */
#define MAX_GRASS_STRUCTURES 5

/* The percent of structure stone zone blocks */
#define MAX_STONE_STRUCTURES 5


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
		
		Cell** getCellMap();
		Block** getBlockMap();
		int getWidth();
		int getHeight();
		int getBlocksHor();
		int getBlocksVert();

	private:
		bool createBlockMap();
		void generateZones();
		void generateMiniBosses();
		void generatePlayers();
		void generatePlaceholderBlocks();
		BlockType makeBlockType(BlockZone z, int rRoll);

		Cell** cellMap;
		Block** blockMap;
		int width;
		int height;
		int bWidth;
		int bHeight;
		int stoneWidth;
		int stoneHeight;
};

#endif