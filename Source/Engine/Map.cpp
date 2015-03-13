/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Map.cpp
--
-- PROGRAM:
--
-- FUNCTIONS:
--          Map(const uint height, const uint width)
--          unsigned int getHeight() const
--          unsigned int getWidth() const
--          void setCell(const uint x, const uint y, const Cell& cell)
--          Cell getCell(const uint x, const uint y) const
--          void setTexture(const uint texture_id)
--          uint getTexture() const
--
-- DATE: February 16, 2015
--
-- REVISIONS: N/A
--
-- DESIGNER: Marc Rafanan
--           Marc Vouve
--
-- PROGRAMMER: Marc Rafanan
--
-- NOTES:
--      This file implements the Map class members
----------------------------------------------------------------------------------------------------------------------*/
#include "Map.h"

using namespace Marx;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Map
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--           Marc Vouve
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: Map()
--
-- PARAMETERS:
--     width    -    unsigned int, width of the map.
--
-- RETURNS:
--     void
--
-- NOTES:
--     Map constructor
--
----------------------------------------------------------------------------------------------------------------------*/
Map::Map(const uint height, const uint width) : width_(width), height_(height), cells_(std::vector<Cell*>(width * height))
{

}


Map::~Map()
{
	// Empty for now
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setCell
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--           Marc Vouve
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: setCell(int x, int y)
--
-- PARAMETERS:
--     x    -    row
--     y    -    column
--
-- RETURNS:
--     void
--
-- NOTES:
--     Sets cell(x, y) in map
--
----------------------------------------------------------------------------------------------------------------------*/
void Map::setCell(const uint x, const uint y, Cell* cell)
{
    uint index = x * width_ + y;
    cells_[index] = cell;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getCell
--
-- DATE: February 16, 2015
--
-- REVISIONS: February 21, 2015    - Changed cells form a 2d array to a 
--                                  vector.
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: getCell(const int& index)
--
-- PARAMETERS:
--     x    - usingned int x coordinate of the cell in the map
--     y    - unsinged int y coordinate of the cell in the map
--
-- RETURNS:
--     Cell
--
-- NOTES:
--     Gets the cell specified by the index (x * width + y) of the Map
--
----------------------------------------------------------------------------------------------------------------------*/
Cell* Map::getCell(const uint x, const uint y) const
{
    uint index = x * width_ + y;
    return cells_[index];
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getWidth
--
-- DATE: February 16, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: getWidth()
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     unsigned int    -    width of the map (in cells)
--
-- NOTES:
--     returns width of the map in cells.
--
----------------------------------------------------------------------------------------------------------------------*/
unsigned int Map::getWidth() const
{
    return width_;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getHeigth
--
-- DATE: February 16, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: getHeight()
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     unsigned int    -    height of the map (in cells)
--
-- NOTES:
--     returns height of the map in cells.
--
----------------------------------------------------------------------------------------------------------------------*/
unsigned int Map::getHeight() const
{
    return height_;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setTexture
--
-- DATE: February 27, 2015
--
-- REVISIONS:
--
-- DESIGNER: Melvin Loho
--           Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: void setTexture(const uint& texture_id)
--
-- PARAMETERS:
--     unsigned int    -    texture id of the map
--
-- RETURNS:
--     void
--
-- NOTES:
--     returns texture id of the map in cells.
--
----------------------------------------------------------------------------------------------------------------------*/
void Map::setTexture(const uint texture_id)
{
    texture_id_ = texture_id;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getTexture
--
-- DATE: February 27, 2015
--
-- REVISIONS:
--
-- DESIGNER: Melvin Loho
--           Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: uint getTexture()
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     unsigned int    -    texture id of the map
--
-- NOTES:
--     returns texture id of the map.
--
----------------------------------------------------------------------------------------------------------------------*/
uint Map::getTexture() const
{
    return texture_id_;
}

