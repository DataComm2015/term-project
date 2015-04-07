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
	if ((hit = me->rMove(vector, time*2, true)) != nullptr)
	{
		if (hit != (static_cast<Projectile*>(me))->getShooter())
		{
			if (Manager::ProjectileManager::getServer())
			{
				onHit(me, hit);
			}	
			me->onDestroy();	
		}
	}
	
}

void AttackAction::onHit(Entity * me, Entity *e)
{
    ServerNetworkController *cont = (ServerNetworkController*)((Projectile*)me)->getShooter()->getController();
    ServerNetworkController *contEnemy = (ServerNetworkController*)((Projectile*)e)->getShooter()->getController();
    /*           Set Health            */
    SetHealthEvent event(cont->getId(), damage);
	
    contEnemy->addEvent(&event);
    /*           Set Points            */

}
