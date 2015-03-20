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

namespace Marx
{
	class Projectile;
	class Entity;
}

#include <functional>
#include <set>
#include "Projectile.h"
#include "Entity.h"

namespace Manager
{
	class ProjectileManager
	{
		private:
			static std::set<Marx::Projectile*> projectile_pool;
		public:
			static Marx::Projectile* getProjectile(float, float, Marx::Controller *, float, float);
			static void enqueue(Marx::Projectile*);
			static void dequeue(Marx::Projectile*);
	};
}

#endif
