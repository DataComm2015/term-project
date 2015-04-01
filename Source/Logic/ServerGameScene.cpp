#include "ServerGameScene.h"

#include "Entities/ServerGameState.h"
#include "ServerCommand.h"
#include "EntityFactory.h"
#include "Creature.h"
#include "Artificial Intelligence/Behaviour.h"
#include "Entities/ServerEnemyController.h"
#include "../Network/Message.h"
#include "EnemyControllerInit.h"
#include "NetworkEntityPairs.h"
#include "Entities/PlayerEntity.h"
#include "Entities/ServerVesselController.h"
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
        timer -= time.asSeconds();
    }
    else
    {
        command->goToScoreboard();
    }
	return;
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

    // Generate the game map
	gMap->generateMap(worldSeed, this);

    createPlayers();
	createEnemy(I_DONT_KNOW, NULL, 12.5, 12.5);
	createEnemy(BASIC_TYPE, NULL, 12.5, 12.5);
	createEnemy(I_DONT_KNOW, NULL, 12.5, 12.5);
	createEnemy(I_DONT_KNOW, NULL, 12.5, 12.5);
	createEnemy(BASIC_TYPE, NULL, 12.5, 12.5);
}

void ServerGameScene::leaveScene()
{
    std::vector<Creature*>::iterator itr = enemies.begin();
    while (itr != enemies.end())
    {
        //NetworkEntity *controller = dynamic_cast<NetworkEntity*>((*itr)->getEntity()->getController());
        //command->getGameState()->unregisterFromAllPlayers(controller);
    }

    enemies.clear();
}

int ServerGameScene::getWorldSeed()
{
    return worldSeed;
}

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
    ServerEnemyController *enemyController = new ServerEnemyController(behaviour);
    enemies.push_back((Creature*)EntityFactory::getInstance()->makeEntity(type,enemyController,cMap,x,y));
    enemyController->init();
    command->getGameState()->registerWithAllPlayers(enemyController, &msg);
}

/**

  Designer: Jeff Bayntun, Eric Tsang
  Coder:    Jeff Bayntun
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
    int vesselNo = 0;
    int vesselX = 0;
    int vesselY = 0;

    // make ServerNetworkController for each vessel
    for(auto it = players.begin(); it != players.end(); ++it)
    {
        currPlayer = it->second;
        currSession = it->first;
        mode = currPlayer->getMode();

        switch(mode)
        {
            case PLAYER_MODE::VESSEL:
            {
                // create the controller, and bind it with the player
                ServerNetworkController* cont = new ServerNetworkController();
                currPlayer->setController(cont);

                // register the vessel controller with all clients
                EnemyControllerInit initData;
                initData.type = ENTITY_TYPES::VESSEL;
		        gMap->getVesselPosition(vesselNo++, &vesselX, &vesselY);
                initData.x = (float) vesselX;
                initData.y = (float) vesselY;

                Message msg;
                msg.data = (void*) &initData;
                msg.len = sizeof(initData);

                // create vessel, pass it server vessel controller too
                Entity* e = EntityFactory::getInstance()->makeEntityFromNetworkMessage(cMap,&msg,cont);

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
