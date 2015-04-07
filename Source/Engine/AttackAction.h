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
	class AttackAction : public Action
	{
		public:
			AttackAction(float, float);
			virtual void onUpdate(Entity * me, float);
			virtual void onHit(Entity * me, Entity * e );
			float getDamage() { return damage; };
		private:
			float damage;
	};
};

#endif
