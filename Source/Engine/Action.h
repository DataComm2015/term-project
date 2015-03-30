/*
This class is a pure virtual class that details implementation for the Projectiles action


*/

#include <SFML/System/Time.hpp>

namespace Marx
{
	class Action
	{
		protected:
			sf::Time TTL;
		public:
			Action(sf::Time _TTL) : TTL(_TTL) {}
			virtual void onUpdate(sf::Time) = 0;
			virtual void onHit(Entity * e ) = 0;
			sf::Time getTTL(){ return TTL }
	}
}
