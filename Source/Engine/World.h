#ifndef WORLD_H_
#define WORLD_H_

//#include "Entity.h"
#include "Lobby.h"
//#include "EntityManager.h"
#include "Map.h"

namespace Marx
{
	/* 
	*	World Class. Contains the map, entities, and lobby for the game.
	*/
	class World
	{
		public:
			//void setEntities(const vector<Entity*> entities);
			void setLobby(const Lobby& lobby);
			//void setEntityManager(const EntityManager manager);
			void setMap(const Map& map);

			//vector<Entity*> getEntities();
			Lobby getLobby();
			//EntityManager getEntityManager();
			Map getMap();
		private:
			//vector<Entity*>	entities_;
			Lobby			lobby_;
			//EntityManager	manager_;
			Map				map_;
	};
}

#endif /* WORLD_H_ */