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
	Entity *hit;
	sf::Vector2f vector = (static_cast<Projectile*>(me))->getVector();
	vector.x *= -1;
	vector.y *= -1;
	/*(static_cast<Projectile*>(me))->setTTL((static_cast<Projectile*>(me))->getTTL() - time);
	MoveEvent * m = new MoveEvent((static_cast<Projectile*>(me))->getVector().x,
													 (static_cast<Projectile*>(me))->getVector().y, 0, 0, true);
*/
	//me->getController()->addEvent(m);
	if ((hit = me->rMove(vector, time*5, true)) != nullptr)
	{
		if (hit != (static_cast<Projectile*>(me))->getShooter())
		{
			std::cout << "AttackAction::hit not me" << std::endl;
			if (Manager::ProjectileManager::getServer())
			{
				std::cout << "AttackAction:: hit server " << std::endl;
				onHit(me, hit);
			}
			me->onDestroy();
		}
	}

}

void AttackAction::onHit(Entity * me, Entity *e)
{
	std::cout << "On Hit " << e << std::endl;
    ServerNetworkController *cont = (ServerNetworkController*)((Projectile*)me)->getShooter()->getController();
    Controller *contEnemy = static_cast<ServerNetworkController*>(e->getController());
    /*           Set Health            */
    SetHealthEvent *event = new SetHealthEvent(cont->getId(), false,damage);
	std::cout << "OnHit event type: " << event->type << std::endl;
    contEnemy->addEvent(event);
    /*           Set Points            */

}
