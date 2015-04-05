#include "Creature.h"

void Creature::setHealth(int health)
{
}

void Creature::setAttack(int attack)
{
}


int Creature::getAttack()
{
	return 0;
}

int Creature::getHealth()
{
	return 0;
}

Marx::Projectile* Creature::createAttack(AttackEvent & event, SGO &sprite, float x, float y)
{
	sf::Vector2f v(event.getCellX(), event.getCellY());
	Marx::Action *action = actionList[event.getAction()];
	return Manager::ProjectileManager::getProjectile(sprite, getEntity()->getMap(),  getEntity(), action, v, 1.0, 1.0);
}

Marx::Projectile* Creature::createSkAttack(SkillAttackEvent& event, SGO &sprite, float x, float y)
{
	sf::Vector2f v(event.getDestX(), event.getDestY());
	Marx::Action *action = actionList[event.getAction()];

	return Manager::ProjectileManager::getProjectile(sprite, getEntity()->getMap(), getEntity(), action, v, 1.0, 1.0);
}

Entity * Creature::getEntity()
{
	// this class should really be refactored to extend entity and be a level between VEntity and Vessal / GK
    return dynamic_cast<Entity *>(this);
}
