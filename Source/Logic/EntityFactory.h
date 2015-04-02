#ifndef _ENTITY_FACTORY_H_
#define _ENTITY_FACTORY_H_

#include "../Multimedia/graphics/object/SGO.h"
#include "../Multimedia/manager/ResourceManager.h"
#include "EntityTypes.h"

namespace Marx
{
    class Controller;
    class Entity;
    class Map;
};

namespace Networking
{
    class Message;
};

/*
 * EntityFactory produces an Enemy of a specified ENEMY_TYPE.
 */
class EntityFactory
{
    public:
        static EntityFactory* getInstance();
        Marx::Entity* makeEntityFromNetworkMessage(
            Marx::Map* cMap,
            Networking::Message* msg,
            Marx::Controller* cont);
        Entity* makeEntity(
            ENTITY_TYPES type,
            Marx::Controller* controller,
            Marx::Map* map,
            float x,
            float y);
    protected:
        EntityFactory();
        ~EntityFactory();
    private:
        static EntityFactory* instance;
        id_resource gkSprite, vesselSprite, structImage;
        SGO gkSGO, vesselSGO, structSprite;
};

#endif
