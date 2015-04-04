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

namespace Marx
{
	class AttackAction : public Action
	{
		public:
			AttackAction(sf::Time, float);
			virtual void onUpdate(Entity * me, sf::Time);
			virtual void onHit(Entity * me, Entity * e );
		private:
			float damage;
	};
}

#endif
