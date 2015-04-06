#ifndef BLOCK_H_
#define BLOCK_H_

#include <vector>
#include "../../Engine/Cell.h"

using std::vector;
using namespace Marx;

/* The width of a block in terms of number of cells */
#define BLOCK_WIDTH 10

/* The height of a block in terms of number of cells */
#define BLOCK_HEIGHT 10

/* The percent of decorative grass tiles */
#define GRASS_DECO_CHANCE 5

/* The percent of decorative stone tiles */
#define STONE_DECO_CHANCE 5

/* The percent of decorative arbiter tiles */
#define ARBITER_DECO_CHANCE 5


/* The zone type of the block */
enum BlockZone {GRASS, STONE, ARBITER};
typedef enum BlockZone BlockZone;

/* The general type of the block */
enum BlockType {EMPTY, P1, P2, P3, P4, ENEMIES, STRUCTURE, MINIBOSS, BOSS};
typedef enum BlockType BlockType;

/* An enum for all possible cell tiles */
enum CellTile {
	GRASS_TL = 1, GRASS_T1, GRASS_T2, GRASS_T3, GRASS_T4, GRASS_TR,
	GRASS_L1, GRASS_1, GRASS_D1, GRASS_D2, GRASS_2, GRASS_R1,
	GRASS_L2, GRASS_3, GRASS_D3, GRASS_D4, GRASS_4, GRASS_R2,
	GRASS_L3, GRASS_5, GRASS_D5, GRASS_D6, GRASS_6, GRASS_R3,
	GRASS_BL, GRASS_CL, GRASS_C1, GRASS_C2, GRASS_CR, GRASS_BR,
	WATER_1, WATER_CL, WATER_C1, WATER_C2, WATER_CR, WATER_2,

	STONE_TL, STONE_T1, STONE_T2, STONE_TR,
	STONE_L1, STONE_D1, STONE_1, STONE_R1,
	STONE_L2, STONE_D2, STONE_D3, STONE_R2,
	STONE_BL, STONE_B1, STONE_B2, STONE_BR,

	ARBITER_TL, ARBITER_T1, ARBITER_T2, ARBITER_TR,
	ARBITER_L1, ARBITER_D1, ARBITER_1, ARBITER_R1,
	ARBITER_L2, ARBITER_D2, ARBITER_D3, ARBITER_R2,
	ARBITER_BL, ARBITER_B1, ARBITER_B2, ARBITER_BR,

	NO_TILE
};
typedef enum CellTile CellTile;


/*
*	The Block class is a collection of cells. Blocks are used
*	to classify chunks of the map in order to define zones,
* 	spawn entities, and handle game balance.
*/
class Block
{
	public:
		Block();
		~Block();
		void setType(BlockType t);
		void setZone(BlockZone z);
		void setCells(vector<Cell*> *cells);
		void setTile(tile_id id);
		void setDeco(vector<CellTile> *tiles);

		Cell* getRandomCell();

		BlockType getType();
		BlockZone getZone();

		char operator()();

	private:
		BlockType type;
		BlockZone zone;
		vector<Cell*> *cellMap;
};

#endif
