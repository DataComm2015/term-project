/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Map.cpp
--
-- PROGRAM: Sojourn
--
-- FUNCTIONS:
--          Map(const uint height, const uint width)
--          unsigned int getHeight() const
--          unsigned int getWidth() const
--          void setCell(const uint x, const uint y, const Cell& cell)
--          Cell getCell(const uint x, const uint y) const
--          void setTexture(const uint texture_id)
--          uint getTexture() const
--          std::set<Entity*> getEntities() const
--          sf::Transform getLocalTransform() const override
--          void drawChildren(Renderer& renderer, sf::RenderStates states) const override
--          void draw(Renderer& renderer, sf::RenderStates states) const override
--
-- DATE: February 16, 2015
--
-- REVISIONS: March 29th - added NULL object cell.
--
-- DESIGNER: Marc Rafanan
--           Marc Vouve
--           Melvin Loho
--
-- PROGRAMMER:
--             Marc Rafanan
--             Melvin Loho
--
-- NOTES:
--      This file implements the Map class members
----------------------------------------------------------------------------------------------------------------------*/
#include "Map.h"
#include "TileManager.h"
#include <iostream>
using namespace Marx;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Map
--
-- DATE: February 16, 2015
--
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
Map::Map(const int height, const int width) : width_(width), height_(height), cells_(std::vector<Cell*>(width * height + 1))
{
	cells_[width * height] = new Cell( -1, -1, 0, true );
}


Map::~Map()
{
	delete cells_[width_ * height_];
	// Empty for now
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getEntities
--
-- DATE: March 29, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: std::set<Entity*> & Map::getEntities()
--
-- PARAMETERS:
--
-- RETURNS:
--     std::set<Entity*>
--
-- NOTES:
--     This iterates through the entire map and returns a collection of the entities contained.
--
----------------------------------------------------------------------------------------------------------------------*/
std::set<Entity*> Map::getEntities() const
{
	std::set<Entity *> entities;
	std::set<Entity *>::iterator it;

	for( Cell * c : cells_ )
	{
		for(Entity * e : c->getEntity())
		{
			entities.emplace(e);
		}
	}

	return entities;
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
void Map::setCell(const int x, const int y, Cell* cell)
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
--			  March 29, 2015		- added null object funcationality.
--
-- DESIGNER: Marc Rafanan
--
-- PROGRAMMER: Marc Rafanan
--			   Marc Vouve
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
Cell* Map::getCell(const int x, const int y) const
{

    if(y < 0 || x < 0 ||x >= width_ || y >= height_ )
    {
    	return *(--cells_.end());
    }

	unsigned int index = (x * width_) + y;

	return cells_.at(index);

	return nullptr;
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
int Map::getWidth() const
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
int Map::getHeight() const
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
--             Melvin Loho
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
--
----------------------------------------------------------------------------------------------------------------------*/
void Map::setTexture(const uint texture_id)
{
    texture_id_ = texture_id;

	// centers the map using the new texture info
	sf::FloatRect* tile = Manager::TileManager::get(getCell(0, 0)->getTileId());
	trans.translate(width_ * tile->width * -0.5, height_ * tile->height * -0.5);
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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getLocalTransform
--
-- DATE: April 3, 2015
--
-- REVISIONS:
--
-- DESIGNER: Melvin Loho
--
-- PROGRAMMER: Melvin Loho
--
-- INTERFACE: sf::Transform Map::getLocalTransform() const
--
-- PARAMETERS:
--
-- RETURNS: the Transform object
--
-- NOTES:
--        Returns the transform object associated with this map.
----------------------------------------------------------------------------------------------------------------------*/
sf::Transform Map::getLocalTransform() const
{
	return trans;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: drawChildren
--
-- DATE: April 3, 2015
--
-- REVISIONS:
--
-- DESIGNER: Melvin Loho
--
-- PROGRAMMER: Melvin Loho
--
-- INTERFACE: void Map::drawChildren(Renderer& renderer, sf::RenderStates states) const
--
-- PARAMETERS:
--             renderer The renderer
--             states The render states
--
-- RETURNS: void
--
-- NOTES:
--        Overrides the drawChildren method which draws all of the entities that have been added to this map.
----------------------------------------------------------------------------------------------------------------------*/
void Map::drawChildren(Renderer& renderer, sf::RenderStates states) const
{
	for (const Entity* e : getEntities())
	{
		renderer.draw(e, states);
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: draw
--
-- DATE: April 3, 2015
--
-- REVISIONS:
--
-- DESIGNER: Melvin Loho
--
-- PROGRAMMER: Melvin Loho
--
-- INTERFACE: void Map::draw(Renderer& renderer, sf::RenderStates states) const
--
-- PARAMETERS:
--             renderer The renderer
--             states The render states
--
-- RETURNS: void
--
-- NOTES:
--        Overrides the draw method which draws this map.
----------------------------------------------------------------------------------------------------------------------*/
void Map::draw(Renderer& renderer, sf::RenderStates states) const
{
	renderer.draw(*this, states);
}
