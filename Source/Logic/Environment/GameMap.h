#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include "../../Engine/Map.h"
#include "Block.h"
#include "../EntityTypes.h"
#include "../../Multimedia/graphics/object/SGO.h"
#include "../../Multimedia/manager/ResourceManager.h"

/* The number of human players in a round */
#define NUM_PLAYERS 4

/* The percent of enemy grass zone blocks */
#define MAX_GRASS_ENEMIES 15

/* The percent of of enemy stone zone blocks */
#define MAX_STONE_ENEMIES 10

/* The percent of structure grass zone blocks */
#define MAX_GRASS_STRUCTURES 5

/* The percent of structure stone zone blocks */
#define MAX_STONE_STRUCTURES 5

/* The minimum size of an enemy group */
#define MIN_ENEMY_GROUP 1

/* The maximum size of an enemy group */
#define MAX_ENEMY_GROUP 3

/* The minimum number of structures in a block */
#define MIN_STRUCTURE_GROUP 1

/* The maximum number of structures in a block */
#define MAX_STRUCTURE_GROUP 3


class ServerGameScene;

/*
*	The GameMap class contains a list of cells, blocks, and functions
*	for generating a map and placing entities into the map.
*/
class GameMap
{
	public:
		GameMap(Marx::Map *cMap);
		~GameMap();
		bool generateMap(int seed, ServerGameScene *scene = NULL);

		Marx::Map* getCellMap();
		Block** getBlockMap();
		int getWidth();
		int getHeight();
		int getBlocksHor();
		int getBlocksVert();

		void getVesselPosition(int vesselNum, int *xPos, int *yPos);

	private:
		bool createBlockMap();
		void setCellBoundaries();
		void generateZones();
		void generateMiniBosses();
		void generatePlayers();
		void generateEnemies();
		void createEnemyGroup(Block *block, BlockZone z, int num);
		void generatePlaceholderBlocks();
		void generateTiles();
		void generateStructures();
		void cleanMap();

		BlockType makeBlockType(BlockZone z, int rRoll);
		ENTITY_TYPES getEnemyType(std::string enemy);

		Marx::Map *cellMap;
		Block** blockMap;
		ServerGameScene *gameScene;
		int width;
		int height;
		int bWidth;
		int bHeight;
		int stoneWidth;
		int stoneHeight;
		bool generated;
};

#endif
