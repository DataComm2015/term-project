#include "Projectile.h"
#include <iostream>

using namespace Marx;

Projectile::Projectile(Map *map, float x, float y, Controller * ctrl = NULL, float h = 1.0, float w = 1.0) :
	Entity(map, x, y, ctrl, h, w)
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
		//onHit(entity);
	
	return entity;
}

void Projectile::onCreate()
{
	//Manager::ProjectileManager.dequeue(this);
}

void Projectile::onDestroy()
{
	//Manager::ProjectileManager.enqueue(this);
}


void Projectile::onUpdate()
{}

