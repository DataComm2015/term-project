#include "Creature.h"
#include "../Engine/AttackAction.h"
#include "EntityFactory.h"
#include "../Engine/Projectile.h"

#include <iostream>

Creature::Creature()
{
	actionList[normalAttack] = new Marx::AttackAction(10, 10, 5);
}

Creature::~Creature()
{
}

void Creature::setHealth(int health)
{
}

int Creature::getSpeed()
{
}

void Creature::setSpeed(int _speed)
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
	std::cout << "Creature Create Attack" << std::endl;
	sf::Vector2f v(event.getCellX(), event.getCellY());

	return EntityFactory::getInstance()->makeProjectile(getEntity()->getMap(),  getEntity(), actionList[normalAttack], v, 1.0, 1.0, NULL);
}

Marx::Projectile* Creature::createSkAttack(SkillAttackEvent& event, SGO &sprite, float x, float y)
{
	sf::Vector2f v(event.getDestX(), event.getDestY());
	//Marx::Action *action = actionList[event.getAction()];

	return EntityFactory::getInstance()->makeProjectile(getEntity()->getMap(), getEntity(), actionList[normalAttack], v, 1.0, 1.0, NULL);
}

Entity * Creature::getEntity()
{
	// this class should really be refactored to extend entity and be a level between VEntity and Vessal / GK
    return dynamic_cast<Entity *>(this);
}
