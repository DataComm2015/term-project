#include "ProjectileManager.h"

std::set<Marx::Projectile*> Manager::ProjectileManager::projectile_pool;
bool Manager::ProjectileManager::SERVER = true;

using namespace Manager;


/* -----------------------------------------------------------------------------
-- Function ProjectileManager::GetProjectile
--
-- Programmer: Thomas Tallentire
--					Marc Vouve
--
-- Designer: Marc Vouve
--
-- Date: ???
--
-- Revision: April 1st - Changed controller creation logic to be handled here.
--	Added Action to projectile.
--
-- Notes:
-- This manager returns instances of projectiles. The controller setup is
-- handle this function.
-- ---------------------------------------------------------------------------*/
Marx::Projectile* ProjectileManager::
getProjectile(SGO &_sprite, Marx::Map *map, float x, float y, float h = 1.0, float w = 1.0)
{
	Marx::Projectile *temp;
	Marx::Controller * cont;
	if (projectile_pool.size() <= 0)
	{
		if( SERVER )
		{
			cont = new ServerNetworkController();
		}
		else
		{
			cont = new ClientNetworkController();
		}

		return new Marx::Projectile(_sprite, map, x, y, cont, h, w);
	} else
	{
		temp = *projectile_pool.begin();
		projectile_pool.erase(*projectile_pool.begin());
		return temp;
	}
}

void ProjectileManager::
enqueue(Marx::Projectile* projectile)
{
	projectile_pool.insert(projectile);
}

void ProjectileManager::
dequeue(Marx::Projectile* projectile)
{
	projectile_pool.erase(projectile);
}

void ProjectileManager::
	setServer(bool serv)
{
	SERVER = serv;
}

bool ProjectileManager::
	getServer()
{
	return SERVER;
}
