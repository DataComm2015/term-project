#include "EntityManager.h"
	
void EntityManager::Add( Entity e )
{
	entities.push_back(e);
}

void EntityManager::Remove( Entity e )
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (entities.at(i) == e)
		{
			// entites.at(i).onDestroy();
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