#include "AttackAction.h"
#include <iostream>

#include <iostream>

using namespace Marx;

AttackAction::AttackAction(float _TTL, float _damage) :
Action(_TTL), damage(_damage), speed(5)
{

}

AttackAction::AttackAction(float _TTL, float _damage, float _speed ) :
Action(_TTL), damage(_damage), speed(_speed)
{

}

void AttackAction::onUpdate(Entity * me, float time)
{
	Entity *hit;
	sf::Vector2f vector = (static_cast<Projectile*>(me))->getVector();
	vector.x *= 1;
	vector.y *= 1;
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

void AttackAction::onHit(Entity * me, Entity *e)
{
    ServerNetworkController *cont = (ServerNetworkController*)((Projectile*)me)->getShooter()->getController();
    Controller *contEnemy = static_cast<ServerNetworkController*>(e->getController());
    /*           Set Health            */
    SetHealthEvent *event = new SetHealthEvent(cont->getId(), false,damage);
    contEnemy->addEvent(event);
    /*           Set Points            */

}
