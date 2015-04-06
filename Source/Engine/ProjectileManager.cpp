#include "ProjectileManager.h"
#include "Controller.h"
#include "../Logic/Event.h"
#include "../Multimedia/manager/ResourceManager.h"
#include "TextureManager.h"
#include "../Multimedia/graphics/object/SGO.h"
#include <iostream>

std::set<Marx::Projectile*> Manager::ProjectileManager::projectile_pool;
ServerCommand * Manager::ProjectileManager::SERVER = nullptr;
Marx::Map * Manager::ProjectileManager::cMap = nullptr;

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
getProjectile(SGO &_sprite, Marx::Map *map,  Marx::Entity * e, Marx::Action *action, sf::Vector2f & v, float h = 1.0, float w = 1.0, Marx::Controller * _cont = NULL)
{
	ProjectileManager::cMap = map;
	std::cout << "Projectile Q: " << projectile_pool.size() << std::endl;
	if (projectile_pool.size() < 1)
	{
		if(SERVER)
		{
			std::cout << "ProjectileManager:: server make proj" << std::endl;
			ServerNetworkController * cont;

			Message msg;
			AttackMessage msgAttk;

			msg.type = Marx::ATTACK;
			msg.data = &msgAttk;
			msg.len = sizeof(AttackMessage);
			msgAttk.srcid = static_cast<ServerNetworkController*>(e->getController())->getId();
			msgAttk.action = normalAttack;
			msgAttk.cellx = v.x;
			msgAttk.celly = v.y;

			std::cout << "Made Attack" << std::endl;

			cont = new ServerNetworkController();
			SERVER->getGameState()->registerWithAllPlayers(cont, &msg);	// thing does here to register
		}
		else
		{
			std::cout << "ProjectileManager:: not server make proj" << std::endl;
			std::cout << "ProjectileManager:: sprite: " << sizeof(_sprite) << std::endl;
			return new Marx::Projectile(_sprite, map, e, e->left, e->top, action, v, _cont, h, w);
		}
	}
	else
	{
		std::cout << "Deck Attack" << std::endl;
		Marx::Projectile* temp = *projectile_pool.begin();
		//temp->setSprite(_sprite);
		temp->setAct(action);
		temp->setTarget(v);
		projectile_pool.erase(*projectile_pool.begin());
		temp->getController()->addEvent(new MoveEvent(e->left, e->top, 1, 1, true));
		return temp;
	}

}

void ProjectileManager::
enqueue(Marx::Projectile * projectile)
{
	projectile_pool.insert(projectile);
	ProjectileManager::cMap->rem(*projectile);
}

void ProjectileManager::
dequeue(Marx::Projectile* projectile)
{
	projectile_pool.erase(projectile);
	ProjectileManager::cMap->add(*projectile);
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
