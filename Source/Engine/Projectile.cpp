#include "Projectile.h"
#include "Event.h"
#include <iostream>
#include <cmath>
#include <map>
#include <SFML/System/Vector2.hpp>

using namespace Marx;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Projectile
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Marc Vouve
--			Thomas Tallentire
--
-- PROGRAMMER: Marc Vouve
--				Thomas Tallentire
--
-- INTERFACE: Projectile::Projectile(SGO &_sprite, Map *map, Entity * e, float x, float y, Action * _act,
--				sf::Vector2f vector, Controller * ctrl = NULL,  float h = 1.0, float w = 1.0)
--
-- PARAMETERS: sprite - The sprite for the projectile
--				map	- The cell map to place the projectile in
--				e	- The entity that created the projectile
--				x	- X location on the cell map to place the projectile
--				y	- Y location on the cell map to place the projectile
--				act - Action to take when a collision occurs
--				vector	- The vector the projectile is moving in
--				ctrl - The controller for the projectile
--				h - Height
--				w - Width
--
-- RETURNS: void
--
-- NOTES:
--        Constructor for a Projectile
--
----------------------------------------------------------------------------------------------------------------------*/
Projectile::Projectile(SGO &_sprite, Map *map, Entity * e, float x, float y, Action * _act, sf::Vector2f vector, Controller * ctrl = NULL,  float h = 1.0, float w = 1.0) :
VEntity(_sprite, map, x, y, ctrl, h, w), act(_act), heading(vector)
{
	TimeToLive = _act->getTTL();
	std::cout << act << std::endl;
	float hy = sqrt( vector.x*vector.x + vector.y*vector.y );
	heading = sf::Vector2f(vector.x / hy, vector.y / hy);
	shooter = e;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: onCreate
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Marc Vouve
--			Thomas Tallentire
--
-- PROGRAMMER: Marc Vouve
--				Thomas Tallentire
--
-- INTERFACE: void Projectile::onCreate()
--
-- PARAMETERS: 
--
-- RETURNS: void
--
-- NOTES:
--        Calls the onCreate of Entity and takes care of the ProjectileManager calls.
--
----------------------------------------------------------------------------------------------------------------------*/
void Projectile::onCreate()
{
	Entity::onCreate();
	drawable = true;
	Manager::ProjectileManager::dequeue(this);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: onDestroy
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Marc Vouve
--			Thomas Tallentire
--
-- PROGRAMMER: Marc Vouve
--				Thomas Tallentire
--
-- INTERFACE: void Projectile::onDestroy
--
-- PARAMETERS: 
--
-- RETURNS: void
--
-- NOTES:
--        Calls the onDestroy of Entity and takes care of the ProjectileManager calls.
--
----------------------------------------------------------------------------------------------------------------------*/
void Projectile::onDestroy()
{
	VEntity::onDestroy();
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: onUpdate
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Marc Vouve
--			Thomas Tallentire
--
-- PROGRAMMER: Marc Vouve
--				Thomas Tallentire
--
-- INTERFACE: void Projectile::onUpdate(float t)
--
-- PARAMETERS: t - The change in time since the last update.
--
-- RETURNS: void
--
-- NOTES:
--        Updates all of the events of the projectile. Calls onUpdate of the Action
--
----------------------------------------------------------------------------------------------------------------------*/
void Projectile::onUpdate(float t)
{
	if(getController() == NULL)
	{
		left = -100;
		top  = -100;

		return;
	}

	Entity *hit;
	if(TimeToLive > 0.0f)
	{
		if (act != nullptr)
		{
			act->onUpdate(this, t);
		}
		else
		{
			std::cout << "No action" << std::endl;
			onDestroy();
		}
		TimeToLive -= t;
	}
	else
	{
		if (top != -100)
		onDestroy();
	}


	// Process events.
	std::vector<Marx::Event*>* eventQueue = getController()->getEvents();
	for(std::vector<Marx::Event*>::iterator it = eventQueue->begin(); it != eventQueue->end(); ++it )
	{
		switch((*it)->type)
		{
			case ::Marx::MOVE:
			{
				MoveEvent * ev = static_cast<MoveEvent*>(*it);
				sf::Vector2f vec(ev->getXDir(), ev->getYDir());
				left = ev->getX();
				top  = ev->getY();
				onCreate();
				setTarget(vec);
				TimeToLive = act->getTTL();
			}
		}
	}

	getController()->clearEvents();

}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setTarget
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Marc Vouve
--			Thomas Tallentire
--
-- PROGRAMMER: Marc Vouve
--				Thomas Tallentire
--
-- INTERFACE: void Projectile::setTarget(sf::Vector2f t)
--
-- PARAMETERS: t - The new heading
--
-- RETURNS: void
--
-- NOTES:
--        Function gets the unit vector in the direction given and updates the heading to it.
--
----------------------------------------------------------------------------------------------------------------------*/
void Projectile::setTarget(sf::Vector2f t)
{
	float hy = sqrt( t.x*t.x + t.y*t.y );

	heading = sf::Vector2f(t.x / hy, t.y / hy);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setCurrentPos
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Marc Vouve
--			Thomas Tallentire
--
-- PROGRAMMER: Marc Vouve
--				Thomas Tallentire
--
-- INTERFACE: void Projectile::setCurrentPos(float x, float y )
--
-- PARAMETERS: float x - The x position to be set to.
--				float y - The y position to be set to.
--
-- RETURNS: void
--
-- NOTES:
--        Function sets the position of the projectile to the given position.
--
----------------------------------------------------------------------------------------------------------------------*/
void Projectile::setCurrentPos(float x, float y )
{
	this->left = x;
	this->top = y;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setAct
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Marc Vouve
--			Thomas Tallentire
--
-- PROGRAMMER: Marc Vouve
--				Thomas Tallentire
--
-- INTERFACE: void Projectile::setAct(Action * act)
--
-- PARAMETERS: Action * act - The action to be set
--
-- RETURNS: void
--
-- NOTES:
--        Function sets the action of the projectile to the given action.
--
----------------------------------------------------------------------------------------------------------------------*/
void Projectile::setAct(Action * act)
{
	TimeToLive = act->getTTL();	// Time to live must be updated within this class. Action should not change it's own time to live.
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getTTL
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: float Projectile::getTTL()
--
-- PARAMETERS: void
--
-- RETURNS: float - The time to live of the projectile
--
-- NOTES:
--        Returns the time to live of the projectile
--
----------------------------------------------------------------------------------------------------------------------*/
float Projectile::getTTL()
{
	return TimeToLive;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setTTL
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Marc Vouve
--
-- PROGRAMMER: Marc Vouve
--
-- INTERFACE: void Projectile::setTTL(float t)
--
-- PARAMETERS: float t - The new time to live
--
-- RETURNS: void
--
-- NOTES:
--        Sets the projectile time to live to the given parameter.
--
----------------------------------------------------------------------------------------------------------------------*/
void Projectile::setTTL(float t)
{
	TimeToLive = t;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getShooter
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: Entity* Projectile::getShooter()
--
-- PARAMETERS: void
--
-- RETURNS: Entity* - The entity that fired the projectile.
--
-- NOTES:
--        Returns the entity that fired the projectile.
--
----------------------------------------------------------------------------------------------------------------------*/
Entity* Projectile::getShooter()
{
	return shooter;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getVector
--
-- DATE: March 15, 2015
--
-- REVISIONS: April 6, 2015
--
-- DESIGNER: Thomas Tallentire
--
-- PROGRAMMER: Thomas Tallentire
--
-- INTERFACE: sf::Vector2f Projectile::getVector()
--
-- PARAMETERS: void
--
-- RETURNS: sf::Vector2f - The current projectile heading.
--
-- NOTES:
--        Returns the current projectile heading.
--
----------------------------------------------------------------------------------------------------------------------*/
sf::Vector2f Projectile::getVector()
{
	return heading;
}
