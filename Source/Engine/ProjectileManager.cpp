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
getProjectile(SGO &_sprite, Marx::Map *map,  float x, float y, Marx::Action *action, sf::Vector2f & v, float h = 1.0, float w = 1.0)
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
			// TODO: Ask Eric about how to get this ID here.
			cont = new ClientNetworkController(0);
		}

		return new Marx::Projectile(_sprite, map, x, y, action, v, cont, h, w);
	} else
	{
		temp = *projectile_pool.begin();
		temp->setSprite(_sprite);
		temp->setCurrentPos(x, y);
		temp->setAct(action);
		temp->setTarget(v);
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
