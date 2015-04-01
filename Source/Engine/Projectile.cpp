#include "Projectile.h"
#include <iostream>

using namespace Marx;

Projectile::Projectile(SGO &_sprite, Map *map, float x, float y, Action * _act, Controller * ctrl = NULL, float h = 1.0, float w = 1.0) :
	VEntity(_sprite, map, x, y, ctrl, h, w), act(_act)
{
	_speed = 0;
}

void Projectile::
setSpeed(float speed)
{
	_speed = speed;
}

Entity * Projectile::move(float x, float y, bool force = false)
{
    Entity *entity;

	entity = Entity::move(x, y, force);

	if (entity != nullptr)
	{
		if (onHit != NULL)
			onHit(entity);
	}


	return entity;
}

void Projectile::onCreate()
{
	Manager::ProjectileManager::dequeue(this);
}

void Projectile::onDestroy()
{
	Manager::ProjectileManager::enqueue(this);
}


void Projectile::onUpdate(sf::Time t)
{
	Action.onUpdate(this, t);
	TimeToLive -= t;
}

void Projectile::setTarget(sf::Vector2f t)
{
	heading = t
}

void Projectile::setCurrentPos(float x, float y )
{
	this.x = x;
	this.y = y;
}

void Projectile::setAct(Action & act)
{
	Action & act = act;
	TimeToLive = act->getTTL();	// Time to live must be updated within this class. Action should not change it's own time to live.
}
