#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: ProjectileManager.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: March 20, 2015
--
-- REVISIONS:
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- NOTES:
-- This class will keep track of projectiles and make new ones when
-- needed.
--
----------------------------------------------------------------------------------------------------------------------*/

#include <functional>
#include <set>
#include "Projectile.h"
#include "Entity.h"
#include "VEntity.h"
#include "Action.h"
#include "../Logic/Entities/ServerNetworkController.h"
#include "../Logic/Entities/ClientNetworkController.h"
#include <SFML/System/Vector2.hpp>
#include "../Logic/ServerCommand.h"
#include "../Network/Message.h"
#include "../Logic/Event.h"
#include "../Logic/Entities/ServerGameState.h"


namespace Marx
{
	class Projectile;
	class Action;
}

namespace Manager
{
	class ProjectileManager
	{
		private:
			static std::set<Marx::Projectile*> projectile_pool;
			static ServerCommand * SERVER;
		public:
			static Marx::Projectile* getProjectile(SGO &, Marx::Map *,  Marx::Entity *, Marx::Action *, sf::Vector2f &, float, float, Marx::Controller *);
			static void enqueue(Marx::Projectile*);
			static void dequeue(Marx::Projectile*);
			static void setServer(ServerCommand *);
			static ServerCommand * getServer();

	};
};

#endif
