/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: EntityFactory.cpp
--
-- PROGRAM: Sojourn
--
-- FUNCTIONS:
--      EntityFactory();
--
-- DATE:
--
-- REVISIONS: N/A
--
-- DESIGNER:
--
-- PROGRAMMER:  Chris Klassen
--
-- NOTES:
--
----------------------------------------------------------------------------------------------------------------------*/



#include "GateKeeperSource/src/GateKeeper.h"
#include "GateKeeperSource/src/Minion.h"
#include "GateKeeperSource/src/MiniBoss.h"
#include "GateKeeperSource/src/MiniBee.h"
#include "EnemyControllerInit.h"
#include "EntityFactory.h"
#include "EntityTypes.h"
#include "Creature.h"
#include "Entities/CommandEntity.h"

#include "../Engine/AttackAction.h"

#include "../Engine/Controller.h"
#include "../Engine/TextureManager.h"

#include "../Network/Message.h"

#include "../Multimedia/graphics/object/SGO.h"

#include "Entities/ProperEntity.h"
#include "Entities/Vessel.h"
#include "Entities/Structure.h"

#include <iostream>
#include <stdlib.h>
 #include <time.h>

using Networking::Message;
using Marx::Controller;
using Marx::Entity;
using Marx::Map;

EntityFactory* EntityFactory::instance = 0;


/******************************************************************************
*   FUNCTION: EntityFactory
*
*   DATE:
*
*   REVISIONS: Filip Gutica     -Added resources and SGOs for different enemy types.
*              Sebastian Pelka  -Added resources for running animation
*              Sebastian Pelka  -Added additional SGOs for weapon types
*              Sebastian Pelka and Sanders Lee
*                               -Warrior/Shaman selection logic
*
*   DESIGNER:
*
*   PROGRAMMER: Chris Klassen
*               Melvin Loho
*               Filip Gutica
*
*   INTERFACE: EntityFactory();
*
*   PARAMETERS:
*
*   RETURNS: nothing
*
*   NOTES:
******************************************************************************/
EntityFactory::EntityFactory()
{
    srand ( time(NULL) );
    // initialize instance variables
    gkSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Enemies/Grass/Guardians/Queen Bee/queen-idle-sheet.png")
    );

    minionSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Enemies/Stone/The Lost/wisp-magma-sheet.png")
    );

    minion2Sprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Enemies/Stone/The Lost/wisp-blue-sheet.png")
    );

    minion3Sprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Enemies/Stone/The Lost/wisp-purple-sheet.png")
    );

    miniBeeSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Enemies/Grass/The Lost/bug-sheet.png")
    );

    miniBossSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Enemies/Stone/Guardians/wanderer-sheet.png")
    );

	  projSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Enemies/projectile-enemy-sheet.png")
    );

    vesselSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Player/Run/Body/vessel-run-sheet.png")
    );

    maskSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Player/Run/Masks/vessel-run-mask01-sheet.png")
    );

    spearSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Player/Run/Weapons/spear-run-sheet.png")
    );

    staffSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Player/Run/Weapons/staff-run-sheet.png")
    );

    gkSGO.sprite().setTexture(*Manager::TextureManager::get(gkSprite));
    gkSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));

    miniBeeSGO.sprite().setTexture(*Manager::TextureManager::get(miniBeeSprite));
    miniBeeSGO.sprite().setTextureRect(sf::IntRect(0, 0, 16, 16));

    minionSGO.sprite().setTexture(*Manager::TextureManager::get(minionSprite));
    minionSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));

    minion2SGO.sprite().setTexture(*Manager::TextureManager::get(minion2Sprite));
    minion2SGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));

    minion3SGO.sprite().setTexture(*Manager::TextureManager::get(minion3Sprite));
    minion3SGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));

    whispSGOs.push_back(minionSGO);
    whispSGOs.push_back(minion2SGO);
    whispSGOs.push_back(minion3SGO);

    miniBossSGO.sprite().setTexture(*Manager::TextureManager::get(miniBossSprite));
    miniBossSGO.sprite().setTextureRect(sf::IntRect(0, 0, 30, 42));

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

    staffSGO.sprite().setTexture(*Manager::TextureManager::get(staffSprite));
    staffSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
}


/******************************************************************************
*   FUNCTION:
*
*   DATE:
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER:
*
*   PROGRAMMER:
*
*   INTERFACE:
*
*   PARAMETERS:
*
*   RETURNS: void
*
*   NOTES:
******************************************************************************/
EntityFactory::~EntityFactory()
{
    // release recourses
}


/******************************************************************************
*   FUNCTION:
*
*   DATE:
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER:
*
*   PROGRAMMER:
*
*   INTERFACE:
*
*   PARAMETERS:
*
*   RETURNS: void
*
*   NOTES:
******************************************************************************/
EntityFactory* EntityFactory::getInstance()
{
    if(instance == 0)
    {
        instance = new EntityFactory();
    }
    return instance;
}


/******************************************************************************
*   FUNCTION:
*
*   DATE:
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER:
*
*   PROGRAMMER:
*
*   INTERFACE:
*
*   PARAMETERS:
*
*   RETURNS: void
*
*   NOTES:
******************************************************************************/
Entity* EntityFactory::makeEntityFromNetworkMessage(
    Map* cMap,
    Message* msg,
    Controller* cont)
{
    if( msg->type == Marx::ATTACK )
    {
	std::cout << "EnittyFactory::makeEntity" << std::endl;
        AttackMessage * ms = (AttackMessage *) msg->data;

        sf::Vector2f v(ms->cellx, ms->celly);
        Marx::AttackAction * action = new Marx::AttackAction(3.0f, 10.0f);

        std::cout << action << std::endl;
        Entity * e = dynamic_cast<Controller*>(NetworkEntityMultiplexer::getInstance()->getEntityById(ms->srcid))->getEntity();

	std::cout << "EnittyFactory::after dynamic_cast" << std::endl;

        return makeProjectile(cMap, e, action, v, 1.0f, 1.0f, cont);

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


/******************************************************************************
*   FUNCTION:
*
*   DATE:
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER:
*
*   PROGRAMMER:
*
*   INTERFACE:
*
*   PARAMETERS:
*
*   RETURNS: void
*
*   NOTES:
******************************************************************************/
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


/******************************************************************************
*   FUNCTION:   makeEntity
*
*   DATE:       April 7, 2015
*
*   REVISIONS:  Filip Gutica     - Add and handle cases for Basic types, Minions,
*                                  mini bees and mini bosses.
*               Sanders Lee      - Added extra entity types so entity selection
*                                  propagates from lobby to server
*
*                 Sebastian Pelka and Sanders Lee
*                                  - Logic for Selecting warrior or shaman
*
*   DESIGNER:
*
*   PROGRAMMER: Filip Gutica
*               Sanders Lee
*
*   INTERFACE:  Entity* EntityFactory::makeEntity(ENTITY_TYPES type,
*                   Controller* cont, Map* map, float x, float y)
*   ENTITY_TYPES type: type of entity to be created
*   Controller* cont: controller to be associated with the entity
*   Map* map: the map the entity is on
*   float x, float y: the coordinates of the entity on the map*
*
*   RETURNS:    Entity* object created by the EntityFactory
*
*   NOTES:
******************************************************************************/
Entity* EntityFactory::makeEntity(
    ENTITY_TYPES type,
    Controller* cont,
    Map* map,
    float x,
    float y)
{
    Entity* entity;
    int classType;

    switch(type)
    {
        case ENTITY_TYPES::BASIC_TYPE:
        {
            GateKeeper *gk = new GateKeeper(gkSGO,map,x,y,cont,1,1);
            entity = gk;
            break;
        }

        case ENTITY_TYPES::VESSEL_WARRIOR:
            entity = new Vessel(vesselSGO, maskSGO, spearSGO,map,x,y,cont,1,1);
            break;
        case ENTITY_TYPES::VESSEL_SHAMAN:
            entity = new Vessel(vesselSGO, maskSGO, staffSGO,map,x,y,cont,1,1);
            break;
        case STRUCTURES:
            //entity = new Structure(structSprite, map, x, y, cont, 1.0, 1.0);
            break;
        case ENTITY_TYPES::MINION:
        {
          int random = rand() % 3;
          GateKeeper *minion = new Minion(whispSGOs[random], map, x, y, cont, 1, 1);
          entity = minion;
          break;
        }
        case ENTITY_TYPES::MINI_BOSS:
        {
          GateKeeper *miniboss = new MiniBoss(miniBossSGO, map, x, y, cont, 1, 1);
          entity = miniboss;
          break;
        }
        case ENTITY_TYPES::MINI_BEE:
        {
          GateKeeper *minibee = new MiniBee(miniBeeSGO, map, x, y, cont, 1, 1);
          entity = minibee;
          break;
        }
        case PROJECTILE:
            //entity = new VEntity(maskSGO, map, x, y, NULL, 1, 1);
            break;
        default:
            break;
    }
    return entity;
}


/******************************************************************************
*   FUNCTION:
*
*   DATE:
*
*   REVISIONS:  Filip Gutica     -  Added cases for Basic types, Minions, mini bees and
*                                     mini bosses.
*
*   DESIGNER:
*
*   PROGRAMMER: Filip Gutica
*
*
*   INTERFACE:
*
*   PARAMETERS:
*
*   RETURNS: void
*
*   NOTES:
******************************************************************************/
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
        {
            GateKeeper *gk = new GateKeeper(gkSGO,map,x,y,cont,1,1);
            entity = gk;
            break;
        }
        case ENTITY_TYPES::VESSEL:
            //
            entity = new Vessel(vesselSGO, maskSGO, spearSGO,map,x,y,cont,1,1);
            break;
        case STRUCTURES:
            //entity = new Structure(id, structSprite, map, x, y, cont, 1.0, 1.0);
            break;
        case ENTITY_TYPES::I_DONT_KNOW:
        case ENTITY_TYPES::BAWS:
        case ENTITY_TYPES::MINION:
        {
          int random = rand() % 3;
          GateKeeper *minion = new Minion(whispSGOs[random], map, x, y, cont, 1, 1);
          entity = minion;
          break;
        }
        case ENTITY_TYPES::MINI_BOSS:
        {
          GateKeeper *miniboss = new MiniBoss(miniBossSGO, map, x, y, cont, 1, 1);
          entity = miniboss;
          break;
        }
        case ENTITY_TYPES::MINI_BEE:
        {
          GateKeeper *minibee = new MiniBee(miniBeeSGO, map, x, y, cont, 1, 1);
          entity = minibee;
          break;
        }
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
    float width,
    Marx::Controller * cont = NULL)
{
    std::cout << "MakeProjectile" << std::endl;
    return Manager::ProjectileManager::getProjectile(projSGO, map, entity, action, v, height, width, cont);
}
