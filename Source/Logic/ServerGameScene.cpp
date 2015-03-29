#include "ServerGameScene.h"

#include "Entities/ServerGameState.h"
#include "ServerCommand.h"
#include "EnemySpawner.h"
#include "Creature.h"
#include "Artificial Intelligence/Behaviour.h"
#include "Entities/ServerEnemyController.h"
#include "../Network/Message.h"
#include "EnemyControllerInit.h"
#include "NetworkEntityPairs.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cerr;
using std::endl;
using Networking::Message;
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

void ServerGameScene::update(sf::Time)
{
	//printf("Update Run Scene\n");
	
	return;
}

void ServerGameScene::processEvents(sf::Event& e)
{
		
}

void ServerGameScene::draw()
{

}

void ServerGameScene::enterScene()
{
    worldSeed = rand();

    // Generate the game map
	gMap->generateMap(worldSeed, this);
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

void ServerGameScene::createEnemy(ENEMY_TYPES type, Behaviour *behaviour, float x, float y)
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
	enemies.push_back(EnemySpawner::createEnemy(type, enemyController, cMap, x, y));
	enemyController->init();
	printf("ENEMY ENTITY TYPE: %d\r\n", enemyController->getType());
	command->getGameState()->registerWithAllPlayers(enemyController, &msg);
}







