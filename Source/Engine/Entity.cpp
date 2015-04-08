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
-- REVISIONS: Julian Brandrick - April 5, 2015
--              -> Added ENTITY_TYPES to constructor
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
Entity::Entity(Map * _map, ENTITY_TYPES eType, float x, float y, Controller * ctrl = NULL, float h = 1.0, float w = 1.0 ) :
    map(_map), sf::FloatRect(x, y, h, w ), controller(ctrl), type(eType)
{
    onCreate();
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
-- FUNCTION: Entity::rMove
--
-- DATE: March 31, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: move(sf::Vector2f & v, float scaler, bool force)
--					sf::Vector2f & v : A unit vector of the position you want to travel to.
--					float scaler : a scaler to apply to the vector.
--					bool force: if the entity can pass through other entities.
--
-- RETURNS: NULL if there is no entity that this entity would collide with. Returns a pointer to an entity that this
--			entity would collide with.
--
-- NOTES: This function provides an interface to move entities relivate to their current position.
--
----------------------------------------------------------------------------------------------------------------------*/
Entity * Entity::rMove( sf::Vector2f& v, float scaler, bool force = false )
{
	return rMove( v.x * scaler, v.y * scaler, force );
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
      if(!blocking)
      {

        if( intersects(*e) && e != this)
  			{
  				return e;
  			}
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
-- REVISIONS: April 6th - Moved out of constructor.
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
    if(controller != NULL)
      controller->setEntity(this);

	  occupiedCells = std::set<Cell*>();

    for(int i = floor(left); i < width + floor(left); i++)
    {
        for(int j = floor(top); j < height + floor(top); j++)
        {
            occupiedCells.emplace(map->getCell(floor(i),floor(j)));
			      map->getCell(floor(i),floor(j))->addEntity(this);
        }
    }

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
    for(Cell * c: occupiedCells )
    {
        c->removeEntity(this);
    }
    top = -100;
    left = -100;
    map->getCell(-1,-1)->addEntity(this);
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
void Entity::onUpdate(float deltaTime)
{
	// logic team
}

/*------------------------------------------------------------------------------
-- FUNCTION: Entity::setBlocking
--
-- DATE: March 30th, 2015
--
-- REVISIONS: 
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: void Entity::setBlocking(bool b)
--							bool b : If the entity is blocking or not.
--							
--
-- RETURNS:
--     void.
--
-- NOTES:
--    This function sets an entity to blocking or non-blocking
--
------------------------------------------------------------------------------*/
void Entity::setBlocking(bool b)
{
	blocking = b;
}

/*------------------------------------------------------------------------------
-- FUNCTION: Entity::getBlocking
--
-- DATE: March 30th, 2015
--
-- REVISIONS: 
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: bool Entity::getBlocking()
--							
--
-- RETURNS:
--     bool - If the entity is blocking or not
--
-- NOTES:
--    This function returns if an entity is blocking or non-blocking
--
------------------------------------------------------------------------------*/
bool Entity::getBlocking()
{
	return blocking;
}

/*------------------------------------------------------------------------------
-- FUNCTION: Entity::getMap
--
-- DATE: March 30th, 2015
--
-- REVISIONS: 
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: Map * Entity::getMap()
--							
--
-- RETURNS:
--     Map* - A pointer to the map the entity is in.
--
-- NOTES:
--    This function returns a pointer to the map the entity is in.
--
------------------------------------------------------------------------------*/
Map * Entity::getMap()
{
    return map;
}

/*------------------------------------------------------------------------------
-- FUNCTION: Entity::getType
--
-- DATE: March 30th, 2015
--
-- REVISIONS: 
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: ENTITY_TYPES Entity::getType()
--							
--
-- RETURNS:
--     ENTITY_TYPES - The type of the entity.
--
-- NOTES:
--    This function returns the type of the entity
--
------------------------------------------------------------------------------*/
ENTITY_TYPES Entity::getType()
{
    return type;
}
