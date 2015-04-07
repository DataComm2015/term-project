#ifndef _ENTITY_FACTORY_H_
#define _ENTITY_FACTORY_H_

#include "../Multimedia/graphics/object/SGO.h"
#include "../Multimedia/manager/ResourceManager.h"
#include "../Engine/ProjectileManager.h"
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
        Entity* makeEntityFromNetworkMessage(
            int id,
            Marx::Map* cMap,
            Networking::Message* msg,
            Marx::Controller* cont);
        Entity* makeEntity(
            ENTITY_TYPES type,
            Marx::Controller* controller,
            Marx::Map* map,
            float x,
            float y);
        Entity* makeEntity(
            int id,
            ENTITY_TYPES type,
            Marx::Controller* controller,
            Marx::Map* map,
            float x,
            float y);
        Marx::Projectile* makeProjectile(
            Marx::Map * map,
            Marx::Entity * entity,
            Marx::Action * action,
            sf::Vector2f & v,
            float height,
            float width,
            Marx::Controller *);
    protected:
        EntityFactory();
        ~EntityFactory();
    private:
        static EntityFactory* instance;

        id_resource gkSprite, minionSprite, minion2Sprite, minion3Sprite, miniBossSprite, miniBeeSprite, projSprite, vesselSprite, maskSprite, spearSprite, staffSprite,structImage;
        SGO gkSGO, minionSGO, projSGO, miniBossSGO, vesselSGO, maskSGO, spearSGO, staffSGO, structSprite;
        SGO minion2SGO, minion3SGO, miniBeeSGO;
        std::vector<SGO> whispSGOs;
};

#endif
