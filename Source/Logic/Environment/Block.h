#ifndef BLOCK_H_
#define BLOCK_H_

#include "../../Engine/Cell.h"

using namespace Marx;

/* The width of a block in terms of number of cells */
#define BLOCK_WIDTH 2

/* The height of a block in terms of number of cells */
#define BLOCK_HEIGHT 2

/* The zone type of the block */
enum BlockZone {GRASS, STONE, ARBITER};
typedef enum BlockZone BlockZone;

/* The general type of the block */
enum BlockType {EMPTY, P1, P2, P3, P4, ENEMIES, STRUCTURE, MINIBOSS, BOSS};
typedef enum BlockType BlockType;

/*
*	The Block class is a collection of cells. Blocks are used
*	to classify chunks of the map in order to define zones,
* 	spawn entities, and handle game balance.
*/
class Block
{
	public:
		Block();
		void setType(BlockType t);
		void setZone(BlockZone z);
		void setCells(Cell** cells);

		BlockType getType();
		BlockZone getZone();

		char operator()();
		
	private:
		BlockType type;
		BlockZone zone;
		Cell** cellMap;
};

#endif