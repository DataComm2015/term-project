#include "ProjectileManager.h"

std::set<Marx::Projectile*> Manager::ProjectileManager::projectile_pool;
ServerCommand * Manager::ProjectileManager::SERVER = nullptr;

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
	Marx::Projectile * temp;


	if (projectile_pool.size() <= 0)
	{
		if( SERVER )
		{
			ServerNetworkController * cont;

			Message msg;
			AttackMessage msgAttk;

			msg.type = Marx::ATTACK;
			msg.data = &msgAttk;
			msg.len = sizeof(AttackMessage);
			/*
			msgAttk.srcid = srcid;
			msgAttk.action = action;
			msgAttk.cellx = xpos;
			msgAttk.celly = ypos;

			msg->add
			*/
			cont = new ServerNetworkController();
			SERVER->getGameState()->registerWithAllPlayers(cont, &msg);	// thing does here to register

			return new Marx::Projectile(_sprite, map, x, y, action, v, cont, h, w);
		}


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
enqueue(Marx::Projectile * projectile)
{
	projectile_pool.insert(projectile);
}

void ProjectileManager::
dequeue(Marx::Projectile* projectile)
{
	projectile_pool.erase(projectile);
}

void ProjectileManager::
	setServer(ServerCommand * serv)
{
	SERVER = serv;
}

ServerCommand * ProjectileManager::
	getServer()
{
	return SERVER;
}
