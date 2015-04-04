#include "ProjectileManager.h"
#include <iostream>

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
getProjectile(SGO &_sprite, Marx::Map *map,  Marx::Entity * e, Marx::Action *action, sf::Vector2f & v, float h = 1.0, float w = 1.0)
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
			msgAttk.srcid = static_cast<ServerNetworkController*>(e->getController())->getId();
			msgAttk.srcx = e->left;
			msgAttk.srcy = e->top;
			msgAttk.action = normalAttack;
			msgAttk.cellx = v.x;
			msgAttk.celly = v.y;

			std::cout << "Made Attack" << std::endl;

			cont = new ServerNetworkController();
			SERVER->getGameState()->registerWithAllPlayers(cont, &msg);	// thing does here to register

			return new Marx::Projectile(_sprite, map, e->left, e->top, action, v, cont, h, w);
		}


	}
	else
	{
		temp = *projectile_pool.begin();
		temp->setSprite(_sprite);
		temp->setCurrentPos(e->left, e->top);
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
