#include "ServerGameScene.h"

#include "Entities/ServerGameState.h"
#include "ServerCommand.h"
#include "EntityFactory.h"
#include "Creature.h"
#include "Artificial Intelligence/Behaviour.h"
#include "Entities/ServerEnemyController.h"
#include "../Network/Message.h"
#include "../Network/NetworkEntity.h"
#include "EnemyControllerInit.h"
#include "NetworkEntityPairs.h"
#include "Entities/PlayerEntity.h"
#include "../GameSettings.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using std::cout;
using std::cerr;
using std::endl;
using Networking::Message;
using Networking::Session;
using Networking::NetworkEntity;
using namespace Marx;

ServerGameScene::ServerGameScene(ServerCommand *command)
    : command(command)
{
	// Create the cell map
	cMap = new Map(90, 90);

	for (int i = 0; i < cMap->getHeight(); i++)
	{
		for (int j = 0; j < cMap->getWidth(); j++)
		{
			Cell *tempCell = new Cell(j, i);
			tempCell->setTileId(1);

			cMap->setCell(j, i, tempCell);
		}
	}

    srand(time(NULL));

	gMap = new GameMap(cMap);
}

ServerGameScene::~ServerGameScene()
{
	delete gMap;

    for (int i = 0; i < enemyControllers.size(); i++)
    {
        delete (enemyControllers[i]);
    }

    for (int i = 0; i < playerList.size(); i++)
    {
        delete (playerList[i]->getController());
        delete (playerList[i]);
    }

	for (int i = 0; i < cMap->getHeight(); i++)
	{
		for (int j = 0; j < cMap->getWidth(); j++)
		{
			delete cMap->getCell(j, i);
		}
	}

	delete cMap;
}


void ServerGameScene::update(sf::Time time)
{

    if (timer > 0)
    {
        // Check if the game round should end
        if (!ALLOW_SINGLE_PLAYER && gameShouldEnd())
        {
            timer = 0;
        }

        /*
        if (syncTimer > 0)
        {
          syncTimer -= time.asSeconds();
        }
        else
        {

          for (int i = 0; i < playerList.size(); i++)
          {
            //Vessel* curVessel = playerList[i];
            //static_cast<ServerNetworkController*>(curVessel->getController())->
              //addEvent(new UpdateEvent(curVessel->left, curVessel->top));
          }

          syncTimer = SYNC_INTERVAL;
        }
        */

        auto entities = cMap->getEntities();
        for ( auto it = entities.begin(); it != entities.end(); ++it)
        {
          (*it)->onUpdate(time.asSeconds());
        }

        for (int i = 0; i < enemyControllers.size(); i++)
            enemyControllers[i]->updateBehaviour(time.asSeconds());
        timer -= time.asSeconds();
    }
    else
    {
        if (lobtimer == SCOREBOARD_LENGTH_SECONDS)
        {
            command->goToScoreboard();
        }
        if (lobtimer > 0)
        {
            lobtimer -= time.asSeconds();
        }
        else
        {
            command->goToLobby();
        }
    }
}


void ServerGameScene::processEvents(sf::Event& e)
{
        Scene::processEvents(e);
}

void ServerGameScene::draw()
{

}

void ServerGameScene::enterScene()
{
    worldSeed = rand();
    timer = GAME_ROUND_LENGTH_SECONDS;
    lobtimer = SCOREBOARD_LENGTH_SECONDS;

    // Generate the game map
	  gMap->generateMap(worldSeed, this);

    createPlayers();
	  //createEnemy(BASIC_TYPE, NULL, 48, 48);
    //createEnemy(MINION, NULL, 48, 48);
    //createEnemy(MINI_BOSS, NULL, 48, 48);
}

void ServerGameScene::leaveScene()
{
    std::vector<Creature*>::iterator itr = enemies.begin();
    while (itr != enemies.end())
    {
        //NetworkEntity *controller = dynamic_cast<NetworkEntity*>((*itr)->getEntity()->getController());
        //command->getGameState()->unregisterFromAllPlayers(controller);
    }

    std::map<Session*, PlayerEntity*> players = command->getGameState()->getPlayers();
    for(auto it = players.begin(); it != players.end(); ++it)
    {
        Vessel *vessel = it->second->getVessel();
	if (vessel)
	{
		NetworkEntity *ne = dynamic_cast<NetworkEntity*>(vessel->getController());
		if (ne)
		{
			command->getGameState()->unregisterFromAllPlayers(ne);
		}
	}
    }

    enemies.clear();
}

int ServerGameScene::getWorldSeed()
{
    return worldSeed;
}

/******************************************************************************
*   FUNCTION: createEnemy
*
*   DATE: April 6 2014
*
*   REVISIONS: Filip Gutica     - Added initializing of the server enemy controller
*                                 adding enemies to the list of gate keepers
*                                 mapping each enemy to a server enemy controller
*
*   DESIGNER:
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: createEnemy(ENTITY_TYPES, Behaviour*, float, float)
*
*   PARAMETERS: type          - Type of enemy to create
*               behaviour     - Behaviour
*               x             - x coordinate
*               y             - y coordinate
*
*   RETURNS: void
*
*   NOTES:
******************************************************************************/
void ServerGameScene::createEnemy(ENTITY_TYPES type, Behaviour *behaviour, float x, float y)
{
    EnemyControllerInit initData;
    initData.type = type;
    initData.x = x;
    initData.y = y;

    Message msg;
    msg.type = 0;
    msg.data = (void*) &initData;
    msg.len = sizeof(initData);

    // Create the enemy
    ServerEnemyController *enemyController = new ServerEnemyController(behaviour, this);
    enemyControllers.push_back(enemyController);

    GateKeeper *entity = static_cast<GateKeeper*>(EntityFactory::getInstance()->makeEntity(type,enemyController,cMap,x,y));

    enemies.push_back((Creature*)entity);
    enemyController->setEntity(static_cast<GateKeeper*>(entity));
    enemyController->init();
    command->getGameState()->registerWithAllPlayers(enemyController, &msg);
}

/*void ServerGameScene::createProjectile(Marx::Action &action, float x, float y)
{
    EnemyControllerInit initData;
    initData.type = ENTITY_TYPES::PROJECTILE;
    initData.x = x;
    initData.y = y;

    Message msg;
    msg.type = 0;
    msg.data = (void*) &initData;
    msg.len = sizeof(initData);

    // Create the enemy
    command->getGameState()->registerWithAllPlayers(enemyController, &msg);

	std::map<Session*, PlayerEntity*> players = command->getGameState()->getPlayers();
	PlayerEntity* currPlayer;

    // create vessel, pass it server vessel controller too
    Entity* e = EntityFactory::getInstance()->makeEntityFromNetworkMessage(cMap,&msg,cont);

    cont->registerSession(currSession,msg);

    command->getGameState()->registerWithAllPlayers(cont,&msg);

}*/

/**

  Designer: Jeff Bayntun, Eric Tsang
  Coder:    Jeff Bayntun, Sanders Lee (Added code for getting player type)
 * @brief ServerGameScene::createPlayers
 * Creates all the vessels and deitys, this includes hooking them up
 * across the network.
 */
void ServerGameScene::createPlayers()
{
    std::map<Session*, PlayerEntity*> players = command->getGameState()->getPlayers();
    PlayerEntity* currPlayer;
    Session* currSession;
    PLAYER_MODE mode;
    PLAYER_TYPE type;
    int vesselNo = 0;
    int vesselX = 0;
    int vesselY = 0;

    // make ServerNetworkController for each vessel
    for(auto it = players.begin(); it != players.end(); ++it)
    {
        currPlayer = it->second;
        currSession = it->first;
        mode = currPlayer->getMode();
        type = currPlayer->getType();
        currPlayer->setSGameScene(this);
	currPlayer->setVessel(NULL);

        switch(mode)
        {
            case PLAYER_MODE::VESSEL:
            {
                // create the controller, and bind it with the player
                ServerNetworkController* cont = new ServerNetworkController();
                currPlayer->setController(cont);

                // register the vessel controller with all clients
                EnemyControllerInit initData;
                switch(type)
                {
                  case PLAYER_TYPE::WARRIOR:
                      initData.type = ENTITY_TYPES::VESSEL_WARRIOR;
                      break;
                  case PLAYER_TYPE::SHAMAN:
                      initData.type = ENTITY_TYPES::VESSEL_SHAMAN;
                      break;
                }

		        gMap->getVesselPosition(vesselNo++, &vesselX, &vesselY);
                initData.x = (float) vesselX;
                initData.y = (float) vesselY;

                Message msg;
                msg.data = (void*) &initData;
                msg.len = sizeof(initData);

                // create vessel, pass it server vessel controller too
                Vessel* e = static_cast<Vessel*>(EntityFactory::getInstance()->makeEntityFromNetworkMessage(cMap,&msg,cont));
				currPlayer->setVessel(e);
				e->setPlayerEntity(currPlayer);

                //Add player entities to the list of players
                playerList.push_back(e);

                // register the server controller with the player
                msg.type = (int) ServerNetworkControllerClientNetworkControllerMsgType::FOLLOW_ME;
                cont->registerSession(currSession,msg);

                // register the server controller with clients
                msg.type = (int) ServerNetworkControllerClientNetworkControllerMsgType::NORMAL;
                command->getGameState()->registerWithAllPlayers(cont,&msg);
                break;
            }
            case PLAYER_MODE::GHOST:
            {
                break;
            }
            case PLAYER_MODE::DEITY:
            {
                //SeverDeityController* deityController = new DeityController();
                //p->setController(deityController);

                //create deity, pass it controller too.
                break;
            }
        }
    }
}

void ServerGameScene::createStructure(ENTITY_TYPES type, float x, float y)
{
/*
    EnemyControllerInit initData;
    initData.type = ENTITY_TYPES::STRUCTURES;
    initData.x = (float) x;
    initData.y = (float) y;

    Message msg;
    msg.data = (void*) &initData;
    msg.len = sizeof(initData);

    Entity *entity = EntityFactory::getInstance()->makeEntity(type,NULL,cMap,x,y);
    command->getGameState()->registerWithAllPlayers((Networking::NetworkEntity*) entity, &msg);
*/
}

std::vector<Vessel*> *ServerGameScene::getPlayerList()
{
  return &playerList;
}

bool ServerGameScene::gameShouldEnd()
{
    int alive = 0;

    for (int i = 0; i < playerList.size(); i++)
    {
        if (!playerList[i]->checkDeath())
        {
            alive++;
        }
    }

    return (alive <= 0);
}
