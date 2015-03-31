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

#include <SFML/System/Time.hpp>

namespace Marx
{
	class AttackAction : public Action
	{
		public:
			AttackAction(sf::Time, float);
			virtual void onUpdate(sf::Time);
			virtual void onHit(Entity * e );
		private:
			float damage;
	}
}
