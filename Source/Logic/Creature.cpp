#include "Creature.h"

void Creature::setHealth(int health)
{
}

void Creature::setAttack(int attack)
{
}

Marx::Projectile* createAttack(int srcid, enum ActionType actionType, float destx, float desty)
{
	float x, y;
	if (getEntity != NULL)
	{
		x = getEntity.left;
		y = getEntity.top;
	}
	Marx::Action *action = actionList[actionType];
	return Manager::ProjectileManager::getProjectile(x, y, action, destx, desty);
}

Entity *Creature::getEntity()
{
    return NULL;
}
