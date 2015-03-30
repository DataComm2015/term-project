#include "Projectile.h"
#include <iostream>

using namespace Marx;

Projectile::Projectile(SGO &_sprite, Map *map, float x, float y, Controller * ctrl = NULL, float h = 1.0, float w = 1.0) :
	VEntity(_sprite, map, x, y, ctrl, h, w)
{
	_speed = 0;
	_delta_x = 0;
	_delta_y = 0;
	_attack_power = 0;
	_TTL = 1.0;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setVelocity
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Projectile::setVelocity(float speed, float delta_x, float delta_y)
-- float speed: the speed of the projectile
-- float delta_x: the x difference between destination and origin
-- float delta_y: the y difference between destination and origin
--
-- RETURNS: nothing
--
-- NOTES:
-- Sets the projectile with a velocity (speed + direction).
--------------------------------------------------------------------------------------------------------------------*/
void Projectile::setVelocity(float speed, float delta_x, float delta_y)
{
	_speed = speed;
	_delta_x = delta_x;
	_delta_y = delta_y;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setAttackPower
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void setAttackPower(int attack_power)
-- int attack_power: the amount of damage the projectile can do on a 0-defence target
--
-- RETURNS: nothing
--
-- NOTES:
-- Sets the projectile with an attack power. Attack power can be negative for a healing projectile.
--------------------------------------------------------------------------------------------------------------------*/
void setAttackPower(int attack_power)
{
	_attack_power = attack_power;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setTimeToLive
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void setTimeToLive(float ttl)
-- float ttl: time in seconds for the projectile to exist
--
-- RETURNS: nothing
--
-- NOTES:
-- Sets the projectile with a time to live.
--------------------------------------------------------------------------------------------------------------------*/
void setTimeToLive(float ttl)
{
	if (ttl > 0.0)
		_TTL = ttl;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: move
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:  Thomas Tallentire
--					  Sanders Lee
--
-- PROGRAMMER:	Thomas Tallentire
--							Sanders Lee
--
-- INTERFACE: Entity * Projectile::move(float x, float y, float delta_t, bool force = false)
--
-- RETURNS: moves the projectile according to starting point and velocity
--
-- NOTES:
--------------------------------------------------------------------------------------------------------------------*/
Entity * Projectile::move(float x, float y, float delta_t, bool force = false)
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


void Projectile::onUpdate()
{}
