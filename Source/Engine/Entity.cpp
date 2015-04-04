/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Entity.cpp
--
-- PROGRAM:
--
-- FUNCTIONS:
--            Entity::Entity(Controller ctrl)
--            Entity::~Entity()
--            void Entity::turn()
--            Entity move(float x, float y, bool force = false ) // not implemented yet
--            bool Entity::checkCollision( Entity entity )
--            std::set<Marx::Cell> Entity::getCells()
--            void Entity::onCreate()
--            void Entity::onDestroy()
--            void Entity::onUpdate()
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Michael Chimick
--			   Marc Vouve
--
-- NOTES:
--        This file implements the Entity class members
--
----------------------------------------------------------------------------------------------------------------------*/
#include "Controller.h"
#include "Entity.h"
#include "Map.h"
#include <iostream>

using namespace Marx;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::Entity
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Michael Chimick
--             Marc Vouve
--
-- INTERFACE: Entity::Entity(Controller ctrl)
--
-- RETURNS: void
--
-- NOTES:
--        Constructor for an Entity
--
----------------------------------------------------------------------------------------------------------------------*/
Entity::Entity(Map * _map, float x, float y, Controller * ctrl = NULL, float h = 1.0, float w = 1.0 ) :
    map(_map), sf::FloatRect(x, y, h, w ), controller(ctrl)
{
    if(ctrl != NULL)
      ctrl->setEntity(this);

	  occupiedCells = std::set<Cell*>();

    for(int i = floor(x); i < width + floor(x); i++)
    {
        for(int j = floor(y); j < height + floor(y); j++)
        {
            occupiedCells.emplace(map->getCell(floor(i),floor(j)));
			      map->getCell(floor(i),floor(j))->addEntity(this);
        }
    }
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::~Entity
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: Entity::~Entity()
--
-- RETURNS: void
--
-- NOTES:
--        Destructor for an entity
--
----------------------------------------------------------------------------------------------------------------------*/
Entity::~Entity()
{
    onDestroy();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::turn
--
-- DATE: February 19, 2015
--
-- REVISIONS: February 20, 2015 - changed to use "Event" class.
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: void Entity::turn()
--
-- RETURNS: void
--
-- NOTES: This doesn't do anything as the base entity, it must be overridden
--
----------------------------------------------------------------------------------------------------------------------*/
void  Entity::turn()
{
    // process events
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::rMove
--
-- DATE: February 29, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: move(float x, float y, bool force)
--					float x: left corner of the entity.
--					float y: top corner of the entity.
--					bool force: if this is true the entity will move even if it will collide with another entity.
--
-- RETURNS: NULL if there is no entity that this entity would collide with. Returns a pointer to an entity that this
--			entity would collide with.
--
-- NOTES: This function provides an interface to move entities relivate to their current position.
--
----------------------------------------------------------------------------------------------------------------------*/
Entity * Entity::rMove(float x, float y, bool force = false)
{
	return aMove(x + left, y + top, force);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:
--
-- DATE: February 19, 2015
--
-- REVISIONS: March 23, 2015 - Added map interaction
--			  March 29, 2015 - Abstracted into rMove and aMove. Leaving this here as depricated.
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: move(float x, float y, bool force)
--					float x: left corner of the entity.
--					float y: top corner of the entity.
--					bool force: if this is true the entity will move even if it will collide with another entity.
--
-- RETURNS: NULL if there is no entity that this entity would collide with. Returns a pointer to an entity that this
--			entity would collide with.
--
-- NOTES: DEPRECATED.
--
----------------------------------------------------------------------------------------------------------------------*/
Entity * Entity::move(float x, float y, bool force = false)
{
	return aMove(x, y, force);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:
--
-- DATE: March 29th
--
-- REVISIONS:
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: move(float x, float y, bool force)
--					float x: left corner of the entity.
--					float y: top corner of the entity.
--					bool force: if this is true the entity will move even if it will collide with another entity.
--
-- RETURNS: NULL if there is no entity that this entity would collide with. Returns a pointer to an entity that this
--			entity would collide with.
--
-- NOTES: DOES NOT RETURN ANYTHING IF A CELL THAT YOU ARE TRYING TO MOVE INTO IS BLOCKING!
--
----------------------------------------------------------------------------------------------------------------------*/
Entity * Entity::aMove(float x, float y, bool force = false)
{
    std::set<Cell*> tempCell;
	float temp_x = left;
	float temp_y = top;
	top = y;
	left = x;
	blocking = !force;
    
	// loop through collecting all cells that this entity will be contained in.
    for(int i = floor(x); i <= width + floor(x); i++)
    {
        for(int j = floor(y); j <= height + floor(y); j++)
        {
            tempCell.emplace(map->getCell(i, j));
		}
    }

	// loop through all cells in the temporary array. looping for
    for(Cell *c : tempCell)
	{
		std::set<Entity*> entities = c->getEntity();

		for( Entity * e : entities )
		{
			if( intersects(*e) && e != this && e->blocking)
			{
				if( !force )
				{
					left = temp_x;
					top = temp_y;
				}

				return e;
			}
		}
	}

	for(Cell * c: occupiedCells )
	{
		c->removeEntity(this);
	}

	for(Cell * c : tempCell )
	{
		c->addEntity(this);
	}


	// checks if any cells are blocking.
	for(Cell *c : tempCell)
		if( c->getBlocking() )	// This doesn't return anything.
		{
			left = temp_x;
			top = temp_y;

			return nullptr;
		}

	occupiedCells = tempCell;

	return nullptr;
}



/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::getCell
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: std::set<Cell> Entity::getCell()
--
-- RETURNS: std::set<Cell>
--
-- NOTES:
--        Returns the occupiedCells of the Entity object
--
----------------------------------------------------------------------------------------------------------------------*/
std::set<Cell*> Entity::getCell()
{
    return occupiedCells;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::getController
--
-- DATE: March 29, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Calvin Rempel
--
-- INTERFACE: Controller* Entity::getController()
--
-- RETURNS: Controller* controller
--
-- NOTES:
--        Returns the Entities controller
--
----------------------------------------------------------------------------------------------------------------------*/
Controller *Entity::getController()
{
    return controller;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::operator==
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: bool Entity::operator==(const Entity& entity)
--
-- RETURNS: bool
--
-- NOTES:
--        Returns true if the entities are the same
--
----------------------------------------------------------------------------------------------------------------------*/
bool Entity::operator==(const Entity& entity)
{
    return false; // for now
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::onCreate
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE: void Entity::onCreate()
--
-- RETURNS: void
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/
void Entity::onCreate()
{
	// logic team
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::onDestroy
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE: void Entity::onDestroy()
--
-- RETURNS: void
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/
void Entity::onDestroy()
{
	// logic team
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::onUpdate
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE: void Entity::onUpdate()
--
-- RETURNS: void
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/
void Entity::onUpdate()
{
	// logic team
}

void Entity::setBlocking(bool b)
{
	blocking = b;
}

bool Entity::getBlocking()
{
	return blocking;
}
