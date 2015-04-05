#ifndef PROJECTILE_H
#define PROJECTILE_H

/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Projectile.h
--
-- PROGRAM:
--
-- FUNCTIONS: N/A
--
-- DATE: March 15, 2015
--
-- REVISIONS:
--
-- DESIGNER: Thomas Tallentire
--					 Sanders Lee
--
-- PROGRAMMER: Thomas Tallentire
--						 Sanders Lee
--
-- NOTES:
--        This file defines the Entity class members
--
----------------------------------------------------------------------------------------------------------------------*/

#include <functional>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include "VEntity.h"
#include "ProjectileManager.h"
#include "Action.h"
#include "Map.h"

namespace Marx
{
	class Projectile : public VEntity
	{
		private:
			float _speed;
			std::function<void(Entity*)> onHit;
			sf::Vector2f heading;
			sf::Time TimeToLive;
			Action * act;
		public:
			Projectile(SGO&, Map*, float, float, Action *, sf::Vector2f, Controller *, float, float);
			Entity * move(float, float, bool);
			virtual void setSpeed(float);
			virtual void onCreate();
			virtual void onDestroy();
			virtual void onUpdate(sf::Time);
			void setTarget(sf::Vector2f t);
			void setCurrentPos(float x, float y );
			void setAct(Action * act);
			sf::Time getTTL();
			void setTTL(sf::Time t);
			sf::Vector2f getVector();
	};
}

#endif
