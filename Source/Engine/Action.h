/*
This class is a pure virtual class that details implementation for the Projectiles action


*/

namespace Marx
{
	class Action
	{
		public:
			virtual void onUpdate(sf::Time) = 0;
			virtual void onHit(Entity * e ) = 0;
	}
}