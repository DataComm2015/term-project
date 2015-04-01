#include "Creature.h"

void Creature::setHealth(int health)
{
}

void Creature::setAttack(int attack)
{
}

Marx::Projectile* Creature::createAttack(AttackEvent& event, float x, float y)
{
	Marx::Action *action = actionList[event.getAction()];
	return Manager::ProjectileManager::getProjectile(x, y, action, event.getCellX(), event.getCellY());
}

Marx::Projectile* Creature::createSkAttack(SkillAttackEvent& event, float x, float y)
{
	Marx::Action *action = actionList[event.getAction()];
	return Manager::ProjectileManager::getProjectile(x, y, action, event.getDestX(), event.getDestY());
}

Entity *Creature::getEntity()
{
    return NULL;
}
