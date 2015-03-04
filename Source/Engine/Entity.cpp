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
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- NOTES:
--        This file implements the Entity class members
--
----------------------------------------------------------------------------------------------------------------------*/
#include "Entity.h"

using namespace Marx;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::Entity
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: Entity::Entity(Controller ctrl)
--
-- RETURNS: void
--
-- NOTES:
--        Constructor for an Entity
--
----------------------------------------------------------------------------------------------------------------------*/
Entity::Entity(Controller ctrl)
{
	controller = ctrl;
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
    std::set<Event> events;
    // process events
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER:
--
-- INTERFACE:
--
-- RETURNS:
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/
/* Leaving this for marc
 *
// This is a bit codey for pseudo-code, but it's done very particular
// this function returns the entity collided with on failure and NULL on success.
Entity move(float x, float y, bool force = false)
{
    if( entity is 1 cell in size )
    {
		Store all cells in the entities range in an std::set without duplicates
        if( !force )	// This argument is passed to check if bounds checking is required
        {
            Check if any entities are overlapping.
			if( entities overlap )
				return other entity
        }
       
       assign collection of cells to this as its cells
        
        // remove from current.
        Remove Entity From Previous Location
        
		Assign Location and bounding location
    }
}*/

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::checkCollision
--
-- DATE: February 20, 2015
--
-- REVISIONS:
--
-- DESIGNER: 	Marc Vouve
--
-- PROGRAMMER: 	Marc Vouve
--
-- INTERFACE: bool Entity::checkCollision( Entity entity )
--
-- RETURNS: bool
--
-- NOTES:
--        Returns true if the entities are in the same cells, else false
--
----------------------------------------------------------------------------------------------------------------------*/
bool Entity::checkCollision( Entity entity )
{
    return false;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::getCells
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: std::set<Marx::Cell> Entity::getCells()
--
-- RETURNS: std::set<Marx::Cell>
--
-- NOTES:
--        Returns the occupiedCells of the Entity object
--
----------------------------------------------------------------------------------------------------------------------*/
std::set<Cell> Entity::getCells()
{
    return occupiedCells;
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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::getRekt
--
-- DATE: February 20, 2015
--
-- REVISIONS: 
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: void Entity::getRekt()
--
-- RETURNS: sf::FloatRect
--
-- NOTES: Gets the location of the entity on the map. 
--
----------------------------------------------------------------------------------------------------------------------*/
sf::FloatRect getRekt()
{
    return location;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Entity::setRekt
--
-- DATE: February 20, 2015
--
-- REVISIONS: 
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: void Entity::setRekt()
--
-- RETURNS: void
--
-- NOTES: Gets the location of the entity on the map. 
--
----------------------------------------------------------------------------------------------------------------------*/
void setRekt(sf::FloatRect l)
{
    location = l;
}