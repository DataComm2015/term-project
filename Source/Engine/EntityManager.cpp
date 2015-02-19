/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE:
--
-- PROGRAM:
--
-- FUNCTIONS:
--
-- DATE:
--
-- REVISIONS:
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/

#include "EntityManager.h"
	
void EntityManager::Add( Entity entity )
{
	entities.push_back(entity);
}

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

void EntityManager::TakeTurn()
{
	for (unsigned int i = 0; i < entities.size(); i++)
    {
    	entities.at(i).turn();
    }
}