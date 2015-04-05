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
	type = EMPTY;
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
*	INTERFACE: void setCells(Cell** cells);
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


/******************************************************************************
*	FUNCTION: setZone
*
*	DATE: February 12, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void setZone(BlockZone z);
*
*	PARAMETERS:
*		z - the zone type to set
*
*	RETURNS:
*		void
*
*	NOTES:
*		This function assigns a zone type to the block.
******************************************************************************/
void Block::setZone(BlockZone z)
{
	zone = z;
}


/******************************************************************************
*	FUNCTION: setType
*
*	DATE: February 12, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void setType(BlockType t);
*
*	PARAMETERS:
*		t - the block type to set
*
*	RETURNS:
*		void
*
*	NOTES:
*		This function assigns a type to the block.
******************************************************************************/
void Block::setType(BlockType t)
{
    type = t;
}


/******************************************************************************
*	FUNCTION: getType
*
*	DATE: February 17, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: BlockType getType();
*
*	PARAMETERS:
*
*	RETURNS:
*		BlockType - the type of the block
*
*	NOTES:
*		This function returns the block's type.
******************************************************************************/
BlockType Block::getType()
{
	return type;
}


/******************************************************************************
*	FUNCTION: getZone
*
*	DATE: February 17, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: BlockZone getZone();
*
*	PARAMETERS:
*
*	RETURNS:
*		BlockZone - the zone of the block
*
*	NOTES:
*		This function returns the block's zone.
******************************************************************************/
BlockZone Block::getZone()
{
	return zone;
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
	switch(type)
	{
		case ENEMIES:
		{
			return 'e';
			break;
		}

		case MINIBOSS:
		{
			return 'M';
			break;
		}

		case BOSS:
		{
			return 'A';
			break;
		}

		case STRUCTURE:
		{
			return 's';
			break;
		}

		case P1:
		{
			return '1';
			break;
		}

		case P2:
		{
			return '2';
			break;
		}

		case P3:
		{
			return '3';
			break;
		}

		case P4:
		{
			return '4';
			break;
		}

		case EMPTY:
		{
			switch(zone)
			{
				case GRASS:
					return '.';
					break;
				case STONE:
					return '*';
					break;
			}

			break;
		}
	}
}