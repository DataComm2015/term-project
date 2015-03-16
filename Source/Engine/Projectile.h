#ifndef PROJECTILE_H
#define PROJECTILE_H

/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Projectile.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: February 19, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Michael Chimick
--
-- NOTES:
--        This file defines the Entity class members
--
----------------------------------------------------------------------------------------------------------------------*/

#include "Entity.h"
#include "ProjectileManager.h"

namespace Marx;
{
	class Projectile : public Entity
	{
		private:
			float _speed;
			ProjectileManager _manager;
		public:
			Projectile(float, float, Controller *, float, float, ProjectileManager&);
			~Projectile();
			
			Entity * move(float, float, bool);
			onHit();
			void setSpeed(float);
	}
}
