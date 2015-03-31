#include "AttackAction.h"

AttackAction::AttackAction(sf::Time _TTL, float _damage) : 
Action(_TTL), damage(_damage) 
{
		
}

void AttackAction::onUpdate(Entity * me, sf::Time time)
{
	me->getController()->addEvent(
}

void AttackAction::onHit(Entity *e)
{
	e->takeDamage(damage);
}
