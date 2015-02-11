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