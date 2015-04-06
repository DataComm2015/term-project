#include "GateKeeperSource/src/GateKeeper.h"
#include "EnemyControllerInit.h"
#include "EntityFactory.h"
#include "EntityTypes.h"
#include "Creature.h"

#include "../Engine/AttackAction.h"

#include "../Engine/Controller.h"
#include "../Engine/TextureManager.h"

#include "../Network/Message.h"

#include "../Multimedia/graphics/object/SGO.h"

#include "Entities/ProperEntity.h"
#include "Entities/Vessel.h"
#include "Entities/Structure.h"

#include <iostream>

using Networking::Message;
using Marx::Controller;
using Marx::Entity;
using Marx::Map;

EntityFactory* EntityFactory::instance = 0;

EntityFactory::EntityFactory()
{
    // initialize instance variables
    gkSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Enemies/Grass/Guardians/Queen Bee/queen-idle-sheet.png")
    );

	projSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Enemies/projectile-enemy-sheet.png")
    );

    vesselSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Player/Idle/Body/vessel-idle.png")
    );

    maskSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Player/Idle/Masks/vessel-idle-mask01.png")
    );

    spearSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Player/Idle/Weapons/spear-idle.png")
    );

    gkSGO.sprite().setTexture(*Manager::TextureManager::get(gkSprite));
    gkSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));

	projSGO.sprite().setTexture(*Manager::TextureManager::get(projSprite));
    projSGO.sprite().setTextureRect(sf::IntRect(0, 0, 8, 8));
    projSGO.sprite().setScale(1, 1);
    projSGO.middleAnchorPoint(true);

    vesselSGO.sprite().setTexture(*Manager::TextureManager::get(vesselSprite));
    vesselSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));

    // Structures
    structImage = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Environment/rock.png")
    );

    structSprite.sprite().setTexture(*Manager::TextureManager::get(structImage));
    structSprite.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));

    maskSGO.sprite().setTexture(*Manager::TextureManager::get(maskSprite));
    maskSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));

    spearSGO.sprite().setTexture(*Manager::TextureManager::get(spearSprite));
    spearSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
}

EntityFactory::~EntityFactory()
{
    // release recourses
}

EntityFactory* EntityFactory::getInstance()
{
    if(instance == 0)
    {
        instance = new EntityFactory();
    }
    return instance;
}

Entity* EntityFactory::makeEntityFromNetworkMessage(
    Map* cMap,
    Message* msg,
    Controller* cont)
{
    if( msg->type == Marx::ATTACK )
    {
        AttackMessage * ms = (AttackMessage *) msg->data;

        sf::Vector2f v(ms->cellx, ms->celly);
        Marx::AttackAction * action = new Marx::AttackAction(10.0f, 10.0f);

        std::cout << action << std::endl;
        return new Marx::Projectile(projSGO, cMap, ms->srcx, ms->srcy, action, v, cont, 1.0, 1.0);

    }
    else
    {
    // Parse Network Message
    EnemyControllerInit* init = (EnemyControllerInit*) msg->data;

    // Init Data:
    // init->type  ENTITY_TYPES
    // init->x     float
    // init->y     float


    // Create the enemy
    return EntityFactory::makeEntity(init->type,cont,cMap,init->x,init->y);
}
}

Entity* EntityFactory::makeEntityFromNetworkMessage(
    int id,
    Map* cMap,
    Message* msg,
    Controller* cont)
{
    // Parse Network Message
    EnemyControllerInit* init = (EnemyControllerInit*) msg->data;

    // Init Data:
    // init->type  ENTITY_TYPES
    // init->x     float
    // init->y     float

    // Create the enemy
    return EntityFactory::makeEntity(id, init->type,cont,cMap,init->x,init->y);
}


Entity* EntityFactory::makeEntity(
    ENTITY_TYPES type,
    Controller* cont,
    Map* map,
    float x,
    float y)
{
    Entity* entity;


    switch(type)
    {
        case ENTITY_TYPES::BASIC_TYPE:
        {
            entity = new GateKeeper(gkSGO,map,x,y,cont,1,1);
            break;
        }
        case ENTITY_TYPES::VESSEL:
            entity = new Vessel(vesselSGO, maskSGO, spearSGO,map,x,y,cont,1,1);
            break;
        case STRUCTURES:
            //entity = new Structure(structSprite, map, x, y, cont, 1.0, 1.0);
            break;
        case ENTITY_TYPES::I_DONT_KNOW:
        case ENTITY_TYPES::BAWS:
        case ENTITY_TYPES::MINION:
        case ENTITY_TYPES::MINI_BOSS:
			break;
        case PROJECTILE:
            //entity = new VEntity(maskSGO, map, x, y, cont, 1, 1);
            break;
        default:
            break;
    }

    return entity;
}

Entity* EntityFactory::makeEntity(
    int id,
    ENTITY_TYPES type,
    Controller* cont,
    Map* map,
    float x,
    float y)
{
    Entity* entity;


    switch(type)
    {
        case ENTITY_TYPES::BASIC_TYPE:
            entity = new GateKeeper(gkSGO,map,x,y,cont,1,1);
            break;
        case ENTITY_TYPES::VESSEL:
            entity = new Vessel(vesselSGO, maskSGO, spearSGO,map,x,y,cont,1,1);
            break;
        case STRUCTURES:
            //entity = new Structure(id, structSprite, map, x, y, cont, 1.0, 1.0);
            break;
        case ENTITY_TYPES::I_DONT_KNOW:
        case ENTITY_TYPES::BAWS:
        case ENTITY_TYPES::MINION:
        case ENTITY_TYPES::MINI_BOSS:
        default:
            break;
    }

    return entity;
}

Projectile* EntityFactory::makeProjectile(
    Marx::Map *  map,
    Marx::Entity * entity,
    Marx::Action * action,
    sf::Vector2f & v,
    float height,
    float width )
{
    std::cout << "Map!" << std::endl;
    return Manager::ProjectileManager::getProjectile(projSGO, map, entity, action, v, height, width);
}
