#ifndef PROJECTILE_H
#define PROJECTILE_H

/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Projectile.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: March 15, 2015
--
-- REVISIONS:
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- NOTES:
--        This file defines the Entity class members
--
----------------------------------------------------------------------------------------------------------------------*/

namespace Marx
{
	class Entity;
}
#include <functional>
#include "Entity.h"
//#include "ProjectileManager.h"

namespace Marx
{
	class Projectile : public Entity
	{
		private:
			float _speed;
			std::function<void(Entity*)> onHit;
		public:
			Projectile(float, float, Controller *, float, float);
			
			Entity * move(float, float, bool);
			void setSpeed(float);
			void onCreate();
			void onDestroy();
			void onUpdate();
	};
}

#endif
