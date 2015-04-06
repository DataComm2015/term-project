#include "Projectile.h"
#include "Event.h"
#include <iostream>
#include <cmath>
#include <map>
#include <SFML/System/Vector2.hpp>

using namespace Marx;

Projectile::Projectile(SGO &_sprite, Map *map, float x, float y, Action * _act, sf::Vector2f vector, Controller * ctrl = NULL,  float h = 1.0, float w = 1.0) :
	VEntity(_sprite, map, x, y, ctrl, h, w), act(_act), heading(vector)
{
    std::cout << act << std::endl;
    float hy = hypot( vector.x , vector.y );
    heading = sf::Vector2f(vector.x / hy, vector.y / hy);
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
    getController()->addEvent(new MoveEvent(-1, -1, 1, 1, true));
	drawable = false;

	Manager::ProjectileManager::enqueue(this);
}


void Projectile::onUpdate(float t)
{
    if(TimeToLive > 0.0f)
    {
        act->onUpdate(this, t);
        //std::cout << "X: " << left << "Y: " << top << "TimeToLive: " << TimeToLive << " Time Removed: " << t << std::endl;
        TimeToLive -= t;
    }
    else
    {
        onDestroy();
    }

    // Process events.
    std::vector<Marx::Event*>* eventQueue = getController()->getEvents();
    for(std::vector<Marx::Event*>::iterator it = eventQueue->begin(); it != eventQueue->end(); ++it )
    {
            switch((*it)->type)
            {
                case ::Marx::MOVE:
                    MoveEvent * ev = static_cast<MoveEvent*>(*it);
                    sf::Vector2f vec(ev->getX(), ev->getY());
                    rMove( vec, t, true );

            }
    }


}

void Projectile::setTarget(sf::Vector2f t)
{
	heading = t;
}

void Projectile::setCurrentPos(float x, float y )
{
	this->left = x;
	this->top = y;
}

void Projectile::setAct(Action * act)
{
    TimeToLive = act->getTTL();	// Time to live must be updated within this class. Action should not change it's own time to live.
}

float Projectile::getTTL()
{
	return TimeToLive;
}


void Projectile::setTTL(float t)
{
	TimeToLive = t;
}

sf::Vector2f Projectile::getVector()
{
	return heading;
}
