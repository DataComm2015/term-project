#include "GameMap.h"


/******************************************************************************
*	FUNCTION: GameMap
*
*	DATE: February 10, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: GameMap(Cell **cMap, int w, int h);
*
*	PARAMETERS:
*		cMap - the cell map to use with the class
*		w - the width of the cell map
*		h - the height of the cell map
*
*	RETURNS:
*		nothing
*
*	NOTES:
*		This is the primary constructor of the GameMap class. 
*
*		This constructor creates a 2D array of cells to be manipulated.
******************************************************************************/
GameMap::GameMap(Cell **cMap, int w, int h)
{
	cellMap = cMap;
	width = w;
	height = h;
}


/******************************************************************************
*	FUNCTION: generateMap
*
*	DATE: February 10, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Chris Klassen
*
*	PROGRAMMER: Chris Klassen
*
*	INTERFACE: bool generateMap();
*
*	PARAMETERS:
*
*	RETURNS:
*		bool - success or failure
*
*	NOTES:
*		This function is responsible for initiating and orchestrating
*		the process of generating a map to start a new round.
******************************************************************************/
bool GameMap::generateMap()
{
	// Calculate the dimensions in block units
	int wBlocks = width / BLOCK_WIDTH;
	int hBlocks = height / BLOCK_HEIGHT;

	// Validate the map dimensions

	// If the width or height is not evenly divisible by the block size
	if (width % BLOCK_WIDTH != 0 || height % BLOCK_HEIGHT != 0)
	{
		return false;
	}

	// If the width or height is not an odd number of blocks
	if (wBlocks % 2 == 0 || hBlocks % 2 == 0)
	{
		return false;
	}

	// Create a block map

	// Define map zones

	// Place the boss

	// Place the players

	// Place mini-bosses

	// Define placeholder blocks

	// Generate enemies

	// Generate miscellaneous objects

	// Generate tiles


	return true;
}


Cell** GameMap::getCellMap()
{
	return cellMap;
}

int GameMap::getWidth()
{
	return width;
}

int GameMap::getHeight()
{
	return height;
}