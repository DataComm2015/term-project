#ifndef BLOCK_H_
#define BLOCK_H_

#include "Cell.h"

/* The width of a block in terms of number of cells */
#define BLOCK_WIDTH 2

/* The height of a block in terms of number of cells */
#define BLOCK_HEIGHT 2

/* The zone type of the block */
enum BlockZone {GRASS, STONE, ARBITER};
typedef enum BlockZone BlockZone;

/* Type of enemy this zone contains - Julian */
enum EnemyType {NONE, MINION, MINIBOSS};
typedef enum EnemyType EnemyType;

/*
*	The Block class is a collection of cells. Blocks are used
*	to classify chunks of the map in order to define zones,
* 	spawn entities, and handle game balance.
*/
class Block
{
	public:
		Block();
		void setEnemy(EnemyType e); // Julian
		void setZone(BlockZone z);
		void setCells(Cell** cells);

		char operator()();
	private:
		EnemyType enemy; // Julian
		BlockZone zone;
		Cell** cellMap;
};

#endif
