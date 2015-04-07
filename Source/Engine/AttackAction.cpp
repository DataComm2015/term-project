#include "AttackAction.h"
#include <iostream>

#include <iostream>

using namespace Marx;

AttackAction::AttackAction(float _TTL, float _damage) :
Action(_TTL), damage(_damage)
{

}

void AttackAction::onUpdate(Entity * me, float time)
{
	(static_cast<Projectile*>(me))->setTTL((static_cast<Projectile*>(me))->getTTL() - time);
	MoveEvent * m = new MoveEvent(me->left, me->top, (static_cast<Projectile*>(me))->getVector().x,
													 (static_cast<Projectile*>(me))->getVector().y, true);

	me->getController()->addEvent(m);
}

void AttackAction::onHit(Entity * me, Entity *e)
{
    ServerNetworkController *cont = (ServerNetworkController*)((Projectile*)me)->getShooter()->getController();
    /*           Set Health            */
    SetHealthEvent event(cont->getId(), damage);
    cont->addEvent(&event);
    /*           Set Points            */

}
