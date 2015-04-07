#ifndef STRUCTURE_H_
#define STRUCTURE_H_


#include <SFML/Graphics.hpp>
#include "../../Network/NetworkEntity.h"
#include "../../Engine/VEntity.h"
#include "../../Engine/Map.h"
#include "../../Engine/Cell.h"
#include "../../Engine/Controller.h"

/*
	The Structure is a simple collidable entity designed to block player
	and enemy movement through the map.

	It is generated server-side and populated for the clients.
*/
class Structure : public Marx::VEntity, public Networking::NetworkEntity
{
	public:
        Structure(int id, SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h, float w);
		Structure(SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h, float w);
		virtual ~Structure();
		virtual void turn();
		virtual void onCreate();
		virtual void onDestroy();
		virtual void onUpdate();
		virtual bool operator==(const VEntity&);

	protected:
		Marx::Controller* _ctrl;
};

#endif
