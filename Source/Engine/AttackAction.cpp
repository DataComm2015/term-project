#include "AttackAction.h"

AttackAction::AttackAction(sf::Time _TTL, float _damage) : 
Action(_TTL), damage(_damage) 
{
		
}

void AttackAction::onUpdate(Entity * me, sf::Time time)
{
	me->setTTL(me->getTTL() - sf::Time time);
	MoveEvent * m = new MoveEvent(left, top, me->getVector().x * 100, me->getVector().y * 100, true);
	
	me->getController()->addEvent(m);
}

void AttackAction::onHit(Entity * me, entity *e)
{
	// give damage / point score event.
}
