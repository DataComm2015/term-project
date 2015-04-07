/*------------------------------------------------------------------------------
-- SOURCE FILE: AttackAction.cpp
--
-- PROGRAM:
--
-- FUNCTIONS: AttackAction::AttackAction(float _TTL, float _damage)
--
-- DATE: March 30, 2015
--
-- REVISIONS: March 31 - April 6 Integration with game.
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
------------------------------------------------------------------------------*/
#include "AttackAction.h"
#include <iostream>

using namespace Marx;
/*------------------------------------------------------------------------------
-- FUNCTION: AttackAction::AttackAction
--
-- DATE: March 30th 2015
--
-- REVISIONS: April 6 Added speed variable.
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--             Thomas Tallentire.
--
-- INTERFACE: AttackAction::AttackAction(float _TTL, float _damage)
--							float _TTL : The time that the action will live.
--							float _damage: The damage to do on hit.
--
--
-- RETURNS:
--     Constructor.
--
-- NOTES:
--     this constructor uses the default speed of 5.
--
------------------------------------------------------------------------------*/
AttackAction::AttackAction(float _TTL, float _damage) :
Action(_TTL), damage(_damage), speed(5)
{

}

/*------------------------------------------------------------------------------
-- FUNCTION: AttackAction::AttackAction
--
-- DATE: March 30th 2015
--
-- REVISIONS: April 6 Added speed variable.
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--             Thomas Tallentire.
--
-- INTERFACE: AttackAction::AttackAction(float _TTL, float _damage, float _speed )
--							float _TTL : The time that the action will live.
--							float _damage: The damage to do on hit.
--              float _speed: the multiplier that the projectile will move.
--
--
-- RETURNS:
--     Constructor.
--
-- NOTES:
--     Projectile movement is calculated using a unit vector assigned to the projectile itself multiplied by the speed
--		assigned here, and the time past each tick. _TTL will establish it's time to live. Projectiles will move approx.
--		_TTL in seconds * speed in world coords.
--
------------------------------------------------------------------------------*/
AttackAction::AttackAction(float _TTL, float _damage, float _speed ) :
Action(_TTL), damage(_damage), speed(_speed)
{

}

/*------------------------------------------------------------------------------
-- FUNCTION: AttackAction::onUpdate
--
-- DATE: March 30th 2015
--
-- REVISIONS: April 6 Added speed variable, removed casting.
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--             Thomas Tallentire.
--
-- INTERFACE: void AttackAction::onUpdate(Projectile * me, float time)
--							Projectile * me : The projectile calling this function.
--							float time: delta time since the last update.
--
--
-- RETURNS:
--     void
--
-- NOTES:
--     The projectile may be destroyed by this function given the following conditions.
--			1) The projectile hits an entity.
--			2) The projectile does not move.
--
------------------------------------------------------------------------------*/
void AttackAction::onUpdate(Projectile * me, float time)
{
	Entity *hit;
	sf::Vector2f vector = me->getVector();
	int tempx = me->left;
	int tempy = me->top;

	if ((hit = me->rMove(vector, time * speed, true)) != nullptr)
	{
		// If the projectile didn't move this update it's probably stuck, delete.
		if(tempx == me->left && tempy == me->top)
		{
			me->onDestroy();
		}

		if (hit != (static_cast<Projectile*>(me))->getShooter())
		{
			if (Manager::ProjectileManager::getServer())
			{
				onHit(me, hit);
			}
			me->onDestroy();
		}
	}

}


/*------------------------------------------------------------------------------
-- FUNCTION: AttackAction::onHit
--
-- DATE: March 30th 2015
--
-- REVISIONS: April 6 Added speed variable, removed casting.
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--             Thomas Tallentire.
--
-- INTERFACE: void AttackAction::onUpdate(Projectile * me, float time)
--							Projectile * me : The projectile calling this function.
--							float time: delta time since the last update.
--
-- RETURNS:
--     void
--
-- NOTES:
--     This function is only called in onUpdate. It will be destroyed at the
--		 end of the turn.
--
------------------------------------------------------------------------------*/
void AttackAction::onHit(Projectile * me, Entity *e)
{
    ServerNetworkController *cont = (ServerNetworkController*)me->getShooter()->getController();
    Controller *contEnemy = static_cast<ServerNetworkController*>(e->getController());
    /*           Set Health            */
    SetHealthEvent *event = new SetHealthEvent(cont->getId(), false,damage);
    contEnemy->addEvent(event);
    /*           Set Points            */

}
