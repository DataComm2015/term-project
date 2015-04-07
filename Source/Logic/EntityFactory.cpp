/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: EntityFactory.cpp
--
-- PROGRAM: Sojourn
--
-- FUNCTIONS:
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
*   REVISIONS: (Date and Description)
*
*   DESIGNER:
*
*   PROGRAMMER: Chris Klassen
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
    // initialize instance variables
    gkSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Enemies/Grass/Guardians/Queen Bee/queen-idle-sheet.png")
    );

    minionSprite = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Enemies/Stone/The Lost/wisp-magma-sheet.png")
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

    minionSGO.sprite().setTexture(*Manager::TextureManager::get(minionSprite));
    minionSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));

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
Entity* EntityFactory::makeEntity(
    ENTITY_TYPES type,
    Controller* cont,
    Map* map,
    float x,
    float y)
{
    Entity* entity;
    int classType;

    //sanderschangestart
    /*std::cout << "WHAT IS HAPPENING??" << std::endl;

    //check the PLC for the value of the class type
    ClientMux* cm = static_cast<ClientMux*>(NetworkEntityMultiplexer::getInstance());
        std::cout << "got a cm" << std::endl;
    if ( cm->getCommandEntity() != NULL)
    {
          std::cout << "cm not null" << std::endl;
          PLAYER_MODE characterType = cm->getCommandEntity()->getPlayerMode();
          std::cout << "got the character type" << std::endl;
          switch (characterType)
          {
              case PLAYER_MODE::VESSEL:
                classType = (int) cm->getCommandEntity()->getLobbyOption()->vesselChoice;
                break;
              case PLAYER_MODE::DEITY:
                classType = (int) cm->getCommandEntity()->getLobbyOption()->deityChoice;
                break;
          }
    //sanderschangeend*/
          switch(type)
          {
              case ENTITY_TYPES::BASIC_TYPE:
              {
                  GateKeeper *gk = new GateKeeper(gkSGO,map,x,y,cont,1,1);
                  entity = gk;
                  break;
              }
              //sanderschangestart
              /*
              case ENTITY_TYPES::VESSEL:
                  std::cout << "making a vessel" << std::endl;
                  if ( classType == 1 )
                  {
                    std::cout << "class type 1" << std::endl;
                    entity = new Vessel(vesselSGO, maskSGO, spearSGO,map,x,y,cont,1,1);
                  }
                  if ( classType == 2 )
                  {
                    std::cout << "class type 2" << std::endl;
                    entity = new Vessel(vesselSGO, maskSGO, staffSGO,map,x,y,cont,1,1);
                  }
                  break;
                  //sanderschangeend*/
              case ENTITY_TYPES::VESSEL_WARRIOR:
                  entity = new Vessel(vesselSGO, maskSGO, spearSGO,map,x,y,cont,1,1);
                  printf("warrior selected whooooooooo\n");
                  break;
              case ENTITY_TYPES::VESSEL_SHAMAN:
                  entity = new Vessel(vesselSGO, maskSGO, staffSGO,map,x,y,cont,1,1);
                  printf("shaman selected whooooooooo\n");
                  break;
              case STRUCTURES:
                  //entity = new Structure(structSprite, map, x, y, cont, 1.0, 1.0);
                  break;
              case ENTITY_TYPES::I_DONT_KNOW:
              case ENTITY_TYPES::BAWS:
              case ENTITY_TYPES::MINION:
              {
                GateKeeper *minion = new Minion(minionSGO, map, x, y, cont, 1, 1);
                entity = minion;
                break;
              }
              case ENTITY_TYPES::MINI_BOSS:
      			       break;
              case PROJECTILE:
                  //entity = new VEntity(maskSGO, map, x, y, cont, 1, 1);
                  break;
              default:
                  break;
          }
          return entity;
    //sanderschangestart
    /*
    }
    else
    {
      std::cout << "null null null" << std::endl;
      return NULL;
    }
    //sanderschangeend*/
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
Entity* EntityFactory::makeEntity(
    int id,
    ENTITY_TYPES type,
    Controller* cont,
    Map* map,
    float x,
    float y)
{
    Entity* entity;

    std::cout << "SDAGDRHDARH" << std::endl;

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
          GateKeeper *minion = new Minion(minionSGO, map, x, y, cont, 1, 1);
          entity = minion;
          break;
        }
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
