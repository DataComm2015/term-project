#include "Block.h"


/******************************************************************************
*	FUNCTION: Block
*
*	DATE: February 11, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: Block();
*
*	PARAMETERS:
*
*	RETURNS:
*		nothing
*
*	NOTES:
*		This is the primary constructor of the Block class. 
*
*		This constructor defines the default zone.
******************************************************************************/
Block::Block()
{
	zone = GRASS;
}


/******************************************************************************
*	FUNCTION: setCells
*
*	DATE: February 11, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: setCells(Cell** cells);
*
*	PARAMETERS:
*		cells - the 2D array of cells to assign to the block
*
*	RETURNS:
*		void
*
*	NOTES:
*		This function assigns a sub-array of cells to the block.
******************************************************************************/
void Block::setCells(Cell** cells)
{
	cellMap = cells;
}


void Block::setZone(BlockZone z)
{
	zone = z;
}

void Block::setEnemy(EnemyType e) // Julian
{
    enemy = e;
}


/******************************************************************************
*	FUNCTION: operator()
*
*	DATE: February 10, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: char operator()();
*
*	PARAMETERS:
*
*	RETURNS:
*		char - the zone character to print to the screen
*
*	NOTES:
*		This function is used for debugging. It returns the zone of the
*		block to the caller.
******************************************************************************/
char Block::operator()()
{
	switch(zone)
	{
		case GRASS:
            if(enemy == MINIBOSS)
            {
                return 'M';
            }
			return '.';
			break;

		case STONE:
            if(enemy == MINIBOSS)
            {
                return 'M';
            }
			return '*';
			break;

		case ARBITER:
			return 'A';
			break;
	}
}