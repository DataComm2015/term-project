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
#include "VEntity.h"

namespace Marx
{
	class Projectile;
}

namespace Manager
{
	class ProjectileManager
	{
		private:
			static std::set<Marx::Projectile*> projectile_pool;
		public:
			static bool SERVER;
			static Marx::Projectile* getProjectile(SGO&, Marx::Map*, float, float, Action &, sf::Vector2f &, Marx::Controller *, float, float);
			static void enqueue(Marx::Projectile*);
			static void dequeue(Marx::Projectile*);
			static void setServer(bool serv);
			static bool getServer();

	};
};

#endif
