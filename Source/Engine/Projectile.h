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
//#include "../AppWindow.h"

namespace Marx
{
	class Action;

	class Projectile : public VEntity
	{
		private:
			std::function<void(Entity*, Entity*)> onHit;
			sf::Vector2f heading;
			float TimeToLive;
			Action * act;
			Entity *shooter;
		public:
			Projectile(SGO&, Map*, Entity *, float, float, Action *, sf::Vector2f, Controller *, float, float);
			Entity * move(float, float, bool);
			virtual void onCreate();
			virtual void onDestroy();
			virtual void onUpdate(float);
			void setTarget(sf::Vector2f t);
			void setCurrentPos(float x, float y );
			void setAct(Action * act);
			float getTTL();
			void setTTL(float t);
			Entity* getShooter();

			sf::Vector2f getVector();
	};
}

#endif
