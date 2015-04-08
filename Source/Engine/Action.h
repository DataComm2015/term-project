/*
This class is a pure virtual class that details implementation for the Projectiles action


*/

#ifndef _ACTION_H_
#define _ACTION_H_

#include <SFML/System/Time.hpp>
#include "Entity.h"
#include "Projectile.h"

namespace Marx
{
	class Projectile;
	
	class Action
	{
		protected:
			float TTL;
		public:
			Action(float _TTL) : TTL(_TTL) {}
			virtual void onUpdate(Projectile * me, float) = 0;
			virtual void onHit(Projectile * me, Entity * e ) = 0;
			float getTTL(){ return TTL; };
	};
};

#endif //_ACTION_H_
