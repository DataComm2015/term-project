/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: AttackAction.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: March 30, 2015
--
-- REVISIONS:
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER:  Thomas Tallentire
--              Marc Vouve
--
-- NOTES:
-- This class will be held by a projectile. It will define the action
-- to be taken when the projectile's on update and onHit are called.
--
----------------------------------------------------------------------------------------------------------------------*/
#ifndef _ATTACKACTION_H_
#define _ATTACKACTION_H_

#include <SFML/System/Time.hpp>
#include "Action.h"
#include "../Logic/Event.h"
#include "Projectile.h"

namespace Marx
{
	class Projectile;
	
	class AttackAction : public Action
	{
		public:
			AttackAction(float, float);
			AttackAction(float, float, float);
			virtual void onUpdate(Projectile*, float);
			virtual void onHit(Projectile*, Entity*);
			float getDamage() { return damage; };
		private:
			float damage;
			float speed;
	};
};

#endif
