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
--					 Sanders Lee
--
-- PROGRAMMER: Thomas Tallentire
--						 Sanders Lee
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
			float _delta_x;
			float _delta_y;
			float _TTL;
			int _attack_power;
			std::function<void(Entity*, int)> onHit;

		public:
			Projectile(Map*, float, float, Controller *, float, float);
			Entity * move(float, float, float, bool);
			void setVelocity(float speed, float delta_x, float delta_y);
			void setAttackPower(int attack_power);
			void setTimeToLive(float delta_t);
			void onCreate();
			void onDestroy();
			void onUpdate();
	};
}

#endif
