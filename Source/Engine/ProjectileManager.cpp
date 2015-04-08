#include "ProjectileManager.h"
#include "Controller.h"
#include "../Logic/Event.h"
#include "../Multimedia/manager/ResourceManager.h"
#include "TextureManager.h"
#include "../Multimedia/graphics/object/SGO.h"
#include "AttackAction.h"
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
--			April 6th - Made projectiles work properly.
--			April 7th - REMOVED FANCY FEATURES TOTS WORKS! (Marc)
--
-- Notes:
-- This manager returns instances of projectiles. The controller setup is
-- handle this function.
-- ---------------------------------------------------------------------------*/
Marx::Projectile* ProjectileManager::
getProjectile(SGO &_sprite, Marx::Map *map,  Marx::Entity * e, Marx::Action *action, sf::Vector2f & v, float h = 1.0, float w = 1.0, Marx::Controller * _cont = NULL)
{
	/*if (projectile_pool.size() <= 1)*/
	{
		if(SERVER)
		{
			Message msg;
			AttackMessage msgAttk;

			msg.type = Marx::ATTACK;
			msg.data = &msgAttk;
			msg.len = sizeof(AttackMessage);
			msgAttk.srcid = static_cast<ServerNetworkController*>(e->getController())->getId();
			msgAttk.action = normalAttack;
			msgAttk.cellx = v.x;
			msgAttk.celly = v.y;

			ServerNetworkController * cont = new ServerNetworkController();
			SERVER->getGameState()->registerWithAllPlayers(cont, &msg);	// thing does here to register
			return new Marx::Projectile(_sprite, map, e, e->left, e->top, action, v, cont, h, w);
		}
		else
		{
			return new Marx::Projectile(_sprite, map, e, e->left, e->top, action, v, _cont, h, w);
		}
	}

	return nullptr;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: enqueue
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Thomas Tallentire
--					Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: void ProjectileManager::
--  enqueue(Marx::Projectile * projectile)
--
-- PARAMETERS: Marx::Projectile * projectile - The projectile to {delete} from the queue.
--
-- RETURNS: void
--
-- NOTES:
--        Cleans up the given projectile.
--
----------------------------------------------------------------------------------------------------------------------*/
void ProjectileManager::
enqueue(Marx::Projectile * projectile)
{
	delete projectile;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: dequeue
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Thomas Tallentire
--					Marc Vouve
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: void ProjectileManager::
--  dequeue(Marx::Projectile * projectile)
--
-- PARAMETERS: Marx::Projectile * projectile - The projectile to {remove} from the queue.
--
-- RETURNS: void
--
-- NOTES:
--        Cleans up the given projectile.
--
----------------------------------------------------------------------------------------------------------------------*/
void ProjectileManager::
dequeue(Marx::Projectile* projectile)
{
	projectile_pool.erase(projectile);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setServer
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: void ProjectileManager::
--				setServer(ServerCommand * serv)
--
-- PARAMETERS: ServerCommand * serv - The server instance
--
-- RETURNS: void
--
-- NOTES:
--        Takes a server instance, used to tell if you are the client or the server.
--
----------------------------------------------------------------------------------------------------------------------*/
void ProjectileManager::
	setServer(ServerCommand * serv)
{
	SERVER = serv;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getServer
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: ServerCommand * ProjectileManager::
--				getServer()
--
-- PARAMETERS: void
--
-- RETURNS: ServerCommand* - The instance of the server if one exists.
--
-- NOTES:
--        Returns the server instance if there is one, can be used as a boolean expression in an if statement.
--
----------------------------------------------------------------------------------------------------------------------*/
ServerCommand * ProjectileManager::
	getServer()
{
	return SERVER;
}

