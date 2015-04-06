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
	std::cout << "Update AttackAction" << std::endl;
	(static_cast<Projectile*>(me))->setTTL((static_cast<Projectile*>(me))->getTTL() - time);
	MoveEvent * m = new MoveEvent(me->left, me->top, (static_cast<Projectile*>(me))->getVector().x,
													 (static_cast<Projectile*>(me))->getVector().y, true);

	std::cout << "MOVE CALL" << std::endl;

	me->getController()->addEvent(m);
}

void AttackAction::onHit(Entity * me, Entity *e)
{
    ServerNetworkController *cont = (ServerNetworkController*)e->getController();
    /*           Set Health            */
    SetHealthEvent event(damage);
    cont->addEvent(&event);
    /*           Set Points            */

}
