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

#include <functional>
#include "VEntity.h"
#include "ProjectileManager.h"
#include "Map.h"

namespace Marx
{
	class Projectile : public VEntity
	{
		private:
			float _speed;
			float _delta_x;
			float _delta_y;
			float _TTL;
			int _attack_power;
			std::function<void(Entity*, int)> onHit;

		public:
			Projectile(SGO&, Map*, float, float, Controller *, float, float);

			Entity * move(float, float, bool);
			void setSpeed(float);
			void onCreate();
			void onDestroy();
			void onUpdate();
	};
}

#endif
