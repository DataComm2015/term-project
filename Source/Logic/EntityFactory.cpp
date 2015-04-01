#include "GateKeeperSource/src/GateKeeper.h"
#include "EnemyControllerInit.h"
#include "EntityFactory.h"
#include "EntityTypes.h"
#include "Creature.h"

#include "../Engine/Controller.h"
#include "../Engine/TextureManager.h"

#include "../Network/Message.h"

#include "../Multimedia/graphics/object/SGO.h"

#include "Entities/ProperEntity.h"
#include "Entities/Vessel.h"

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
    gkSGO.sprite().setScale(1, 1);
    gkSGO.middleAnchorPoint(true);

    vesselSGO.sprite().setTexture(*Manager::TextureManager::get(vesselSprite));
    vesselSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
    vesselSGO.sprite().setScale(2, 2);
    vesselSGO.middleAnchorPoint(true);

    maskSGO.sprite().setTexture(*Manager::TextureManager::get(maskSprite));
    maskSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
    maskSGO.sprite().setScale(2, 2);
    maskSGO.middleAnchorPoint(true);

    spearSGO.sprite().setTexture(*Manager::TextureManager::get(spearSprite));
    spearSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
    spearSGO.sprite().setScale(2, 2);
    spearSGO.middleAnchorPoint(true);
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
    // Parse Network Message
    EnemyControllerInit* init = (EnemyControllerInit*) msg->data;

    // Init Data:
    // init->type  ENTITY_TYPES
    // init->x     float
    // init->y     float

    // Create the enemy
    return EntityFactory::makeEntity(init->type,cont,cMap,init->x,init->y);
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
            entity = new GateKeeper(gkSGO,map,x,y,cont,1,1);
            break;
        case ENTITY_TYPES::VESSEL:
            entity = new Vessel(vesselSGO, maskSGO, spearSGO,map,x,y,cont,1,1);
            break;
        case ENTITY_TYPES::I_DONT_KNOW:
        case ENTITY_TYPES::BAWS:
        case ENTITY_TYPES::MINION:
        case ENTITY_TYPES::MINI_BOSS:
        default:
            entity = new ProperEntity(map,x,y,cont,1.0,1.0);
            break;
    }

    return entity;
}
