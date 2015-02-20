#include "Map.h"

using namespace Marx;

/******************************************************************************
*	FUNCTION: Map
*
*	DATE: February 16, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Marc Rafanan
*
*	PROGRAMMER: Marc Rafanan
*
*	INTERFACE: Map()
*
*	PARAMETERS:
*		// void for now
*
*	RETURNS:
*		void
*
*	NOTES:
*		Map constructor
*
******************************************************************************/
Map::Map()
{
	// Initialize Map
}

/******************************************************************************
*	FUNCTION: setCell
*
*	DATE: February 16, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Marc Rafanan
*
*	PROGRAMMER: Marc Rafanan
*
*	INTERFACE: setCell(int x, int y)
*
*	PARAMETERS:
*		x	-	row
*		y	-	column
*
*	RETURNS:
*		void
*
*	NOTES:
*		Sets cell(x, y) in map
*
******************************************************************************/
void Map::setCell(const int& x, const int& y, const Cell& cell)
{
	cells_[x][y] = cell;
}

/******************************************************************************
*	FUNCTION: getCell
*
*	DATE: February 16, 2015
*
*	REVISIONS: (Date and Description)
*
*	DESIGNER: Marc Rafanan
*
*	PROGRAMMER: Marc Rafanan
*
*	INTERFACE: getCell(int x, int y)
*
*	PARAMETERS:
*		x	-	row
*		y	-	column
*
*	RETURNS:
*		Cell
*
*	NOTES:
*		Gets the cell in (x, y) of the Map
*
******************************************************************************/
Cell Map::getCell(const int& x, const int& y)
{
	return cells_[x][y];
}
