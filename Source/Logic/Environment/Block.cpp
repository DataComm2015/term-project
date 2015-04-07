/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Block.cpp
--
-- PROGRAM: Sojourn
--
-- FUNCTIONS:
--		Block();
--		~Block();
--		void setCells(vector<Cell> *cells);
--		void setZone(BlockZone z);
--		void setType(BlockType t);
--		void setTile(tile_id id);
--		void setDeco(vector<CellTile> *tiles);
--		Cell* getRandomCell();
--		BlockType getType();
--		BlockZone getZone();
--		BlockZone getZone();
--
-- DATE: February 11, 2015
--
-- REVISIONS: N/A
--
-- DESIGNER: Chris Klassen
--
-- PROGRAMMER:  Chris Klassen
--
-- NOTES:
--        This file contains the implementation of the block class.
--		  The block is a logical segment of the game map.
----------------------------------------------------------------------------------------------------------------------*/


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
*	FUNCTION: ~Block
*
*	DATE: February 11, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: ~Block();
*
*	PARAMETERS:
*
*	RETURNS:
*		nothing
*
*	NOTES:
*		This is the destructor of the Block class.
******************************************************************************/
Block::~Block()
{
	delete cellMap;
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
*	INTERFACE: void setCells(vector<Cell> *cells);
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
void Block::setCells(vector<Cell*> *cells)
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
*	FUNCTION: setTile
*
*	DATE: March 4, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void setTile(tile_id id);
*
*	PARAMETERS:
*		id - the tile id to assign to each cell in the block
*
*	RETURNS:
*		void
*
*	NOTES:
*		This function assigns a tile to every cell in the block.
******************************************************************************/
void Block::setTile(tile_id id)
{
	for (vector<Cell*>::iterator it = cellMap->begin(); it != cellMap->end(); it++)
	{
		(*it)->setTileId(id);
	}
}


/******************************************************************************
*	FUNCTION: setDeco
*
*	DATE: March 4, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: void setDeco(vector<CellTile> *tiles);
*
*	PARAMETERS:
*		tiles - a vector of possible decorative tiles to use
*
*	RETURNS:
*		void
*
*	NOTES:
*		This function assigns random decorations to the block.
******************************************************************************/
void Block::setDeco(vector<CellTile> *tiles)
{
	int decoChance;
	int randomDeco;

	for (int i = 0; i < (int) cellMap->size(); i++)
	{
			Cell *cell = cellMap->at(i);
			
			if (zone == GRASS)
			{
				decoChance = rand() % 100;
				if (decoChance <= GRASS_DECO_CHANCE)
				{
					randomDeco = rand() % tiles->size();
					cell->setTileId(tiles->at(randomDeco));
				}
			}
			else if (zone == STONE)
			{
				decoChance = rand() % 100;
				if (decoChance <= STONE_DECO_CHANCE)
				{
					randomDeco = rand() % tiles->size();
					cell->setTileId(tiles->at(randomDeco));
				}
			}
			else
			{
				decoChance = rand() % 100;
				if (decoChance <= ARBITER_DECO_CHANCE)
				{
					randomDeco = rand() % tiles->size();
					cell->setTileId(tiles->at(randomDeco));
				}
			}
	}
}


/******************************************************************************
*	FUNCTION: getRandomCell
*
*	DATE: March 31, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: Cell* getRandomCell();
*
*	PARAMETERS:
*
*	RETURNS:
*		Cell* - the cell to return
*
*	NOTES:
*		This function returns a vacant cell within the block.
******************************************************************************/
Cell* Block::getRandomCell()
{
	Cell *tempCell;

	// Search until an empty, unblocking cell is found
	do
	{
		int cellNum = rand() % (BLOCK_WIDTH * BLOCK_HEIGHT);
		tempCell = (*cellMap)[cellNum];
	}
	while (tempCell->getBlocking() || tempCell->getEntity().size() != 0);

	return tempCell;
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