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
*		width	-	unsigned int, width of the map.
*
*	RETURNS:
*		void
*
*	NOTES:
*		Map constructor
*
******************************************************************************/
Map::Map(unsigned int width)
{
	width_ = width;
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
void Map::setCell(const Cell& cell)
{
	cells_.push_back(cell);
}

/******************************************************************************
*	FUNCTION: getCell
*
*	DATE: February 16, 2015
*
*	REVISIONS: February 21, 2015	- Changed cells form a 2d array to a 
* 									vector.
*
*	DESIGNER: Marc Rafanan
*
*	PROGRAMMER: Marc Rafanan
*
*	INTERFACE: getCell(const int& index)
*
*	PARAMETERS:
*		index	- index is computed as x * width + y
*
*	RETURNS:
*		Cell
*
*	NOTES:
*		Gets the cell specified by the index (x * width + y) of the Map
*
******************************************************************************/
Cell Map::getCell(const int& index)
{
	return cells_[index];
}

/******************************************************************************
*	FUNCTION: getWidth
*
*	DATE: February 16, 2015
*
*	REVISIONS:
*
*	DESIGNER: Marc Rafanan
*
*	PROGRAMMER: Marc Rafanan
*
*	INTERFACE: getWidth()
*
*	PARAMETERS:
*		void
*
*	RETURNS:
*		unsigned int	-	width of the map (in cells)
*
*	NOTES:
*		returns width of the map in cells.
*
******************************************************************************/
unsigned int Map::getWidth()
{
	return width_;
}
