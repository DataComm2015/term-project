/*
This class is a pure virtual class that details implementation for the Projectiles action


*/

#ifndef _ACTION_H_
#define _ACTION_H_

#include <SFML/System/Time.hpp>
#include "Entity.h"

namespace Marx
{
	class Action
	{
		protected:
			float TTL;
		public:
			Action(float _TTL) : TTL(_TTL) {}
			virtual void onUpdate(Entity * me, float) = 0;
			virtual void onHit(Entity * me, Entity * e ) = 0;
			float getTTL(){ return TTL; };
	};
};

#endif //_ACTION_H_
