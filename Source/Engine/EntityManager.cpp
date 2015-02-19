/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: EntityManager.cpp
--
-- PROGRAM:
--
-- FUNCTIONS:
--            void EntityManager::Add( Entity entity )
--            void EntityManager::Remove( Entity entity )
--            void EntityManager::TakeTurn()
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
--        This file implements the EntityManager class members
--
----------------------------------------------------------------------------------------------------------------------*/

#include "EntityManager.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: EntityManager::Add
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: void EntityManager::Add( Entity entity )
--
-- RETURNS: void
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/
void EntityManager::Add( Entity entity )
{
	entities.push_back(entity);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: EntityManager::Remove
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: void EntityManager::Remove( Entity entity )
--
-- RETURNS: void
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/
void EntityManager::Remove( Entity entity )
{
    for (unsigned int i = 0; i < entities.size(); i++)
    {
    	if (entities.at(i) == entity)
    	{
    		entities.at(i).onDestroy();
    		entities.erase(entities.begin() + i);
    		return;
    	}
    }
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: EntityManager::TakeTurn
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marx-Engine
--
-- PROGRAMMER: Michael Chimick
--
-- INTERFACE: void EntityManager::TakeTurn()
--
-- RETURNS: void
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/
void EntityManager::TakeTurn()
{
	for (unsigned int i = 0; i < entities.size(); i++)
    {
    	entities.at(i).turn();
    }
}