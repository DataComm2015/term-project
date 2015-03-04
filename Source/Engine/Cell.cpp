/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Cell.cpp
--
-- PROGRAM:
--
-- FUNCTIONS:
--          Cell(int x = 0, int y = 0)
--          void setId(std::string id)
--          std::string getId() const
--          void setTileId(tile_id t_id)
--          tile_id getTileId() const
--          void    setX(const int& x)
--          void    setY(const int& y)
--          void    setCoord(const int& x, const int& y)
--          int     getX() const
--          int     getY() const
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
--      This file implements the Cell class members
----------------------------------------------------------------------------------------------------------------------*/

#include "Cell.h"

using namespace Marx;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setId
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: void setId(string id)
--
-- PARAMETERS:
--     id    -    id for the cell
--
-- RETURNS:
--     void
--
-- NOTES:
--     Sets the ID for the cell
--
----------------------------------------------------------------------------------------------------------------------*/
void Cell::setId(std::string id)
{
        cell_id_ = id;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getId
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: std::string getId()
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     std::string    -    ID of the cell
--
-- NOTES:
--     Gets the ID of the cell
--
----------------------------------------------------------------------------------------------------------------------*/
std::string Cell::getId() const
{
    return cell_id_;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setTileId
--
-- DATE: February 20, 2015
--
-- REVISIONS: February 20, 2015 - Added tile id for the cells
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: void setTileId(tile_id t_id)
--
-- PARAMETERS:
--     t_id    -    tile id for the cell (tile_id typedef'd in Cell.h)
--
-- RETURNS:
--     void
--
-- NOTES:
--     Sets the tile ID for the cell
--
----------------------------------------------------------------------------------------------------------------------*/
void Cell::setTileId(tile_id t_id)
{
    tile_id_ = t_id;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getTileId
--
-- DATE: February 20, 2015
--
-- REVISIONS: February 20, 2015 - added tile id to cells
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: tile_id getTileId()
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     tile_id    -    typedef in Cell.h. Tile ID for the cell
--
-- NOTES:
--     Gets the tile ID of the cell
--
----------------------------------------------------------------------------------------------------------------------*/
tile_id Cell::getTileId() const
{
    return tile_id_;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setX
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: void setX(const int& x)
--
-- PARAMETERS:
--     x    -    x coordinate of the cell in the map
--
-- RETURNS:
--     void
--
-- NOTES:
--     Sets the x coordinate of the cell
--
----------------------------------------------------------------------------------------------------------------------*/
void Cell::setX(const int& x)
{
    xcoord_ = x;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setY
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: void setY(const int& y)
--
-- PARAMETERS:
--     y    -    y coordinate of the cell in the map
--
-- RETURNS:
--     void
--
-- NOTES:
--     Sets the y coordinate of the cell
--
----------------------------------------------------------------------------------------------------------------------*/
void Cell::setY(const int& y)
{
    ycoord_ = y;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setCoord
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: void setCoord(const int& x, const int& y)
--
-- PARAMETERS:
--     x    -    x coordinate of the cell in the map
--     y    -    y coordinate of the cell in the map
--
-- RETURNS:
--     void
--
-- NOTES:
--     Sets the x and y coordinate of the cell
--
----------------------------------------------------------------------------------------------------------------------*/
void Cell::setCoord(const int& x, const int& y)
{
    xcoord_ = x;
    ycoord_ = y;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getX
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: int getX()
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     int    -    x coordinate of the cell
--
-- NOTES:
--     Gets the x coordinate of the cell
--
----------------------------------------------------------------------------------------------------------------------*/
int Cell::getX() const
{
    return xcoord_;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getY
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: int getY()
--
-- PARAMETERS:
--     void
--
-- RETURNS:
--     int    -    y coordinate of the cell
--
-- NOTES:
--     Gets the y coordinate of the cell
--
----------------------------------------------------------------------------------------------------------------------*/
int Cell::getY() const
{
    return ycoord_;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: operator==
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--
-- INTERFACE: bool operator==(const Cell& cell)
--
-- PARAMETERS:
--     cell    -    cell to compare
--
-- RETURNS:
--     bool    -    true or false
--
-- NOTES:
--     Compares 2 cells if they are lying on the same coordinate in a map
--
----------------------------------------------------------------------------------------------------------------------*/
bool Cell::operator==(const Cell& cell)
{
    return (xcoord_ == cell.xcoord_ && ycoord_ == cell.ycoord_) ? true : false;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getEntity
--
-- DATE: February 16, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: getEntity()
--
-- PARAMETERS:
--     cell    -    cell to compare
--
-- RETURNS:
--     std::set<Entity> - set of all the entities currently located inside this cell, stored as pointers in a set.
--
-- NOTES:
--     Returns a list of all the cells in the area.
--
----------------------------------------------------------------------------------------------------------------------*/
std::set<Entity*> Cell::getEntity()
{
	return entity;
}	