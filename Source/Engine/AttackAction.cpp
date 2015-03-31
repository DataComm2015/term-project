#include "AttackAction.h"

AttackAction::AttackAction(sf::Time _TTL, float _damage) : 
Action(_TTL), damage(_damage) 
{
		
}

void AttackAction::onUpdate(sf::Time time)
{
	
}

void AttackAction::onHit(Entity *e)
{
	e->takeDamage(damage);
}
