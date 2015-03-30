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
#include "Entities/PlayerEntity.h"
#include "Entities/ServerVesselController.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

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

    // createPlayers();
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

void ServerGameScene::createEnemy(ENEMY_TYPES type, Behaviour *behaviour, float x, float y)
{
    EnemyControllerInit initData;
	initData.type = type;
	initData.x = x;
	initData.y = y;

  printf("X: %f, Y: %f\n", x, y);

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
    PlayerEntity* p;
    PLAYER_MODE mode;

    int i = 0;

    // make serverCommandEntity for each vessel
    for(auto it = players.begin(); it != players.end(); ++it)
    {
        p = it->second;
        mode = p->getMode();

        printf("I am a player%d!\n",++i);

        if(mode == VESSEL )
        {
            ServerVesselController* cont = new ServerVesselController();
            p->setController(cont);

            printf("I made a vessel! :D\n");

            // making sprite for the vessel. plz move into vessel later
            id_resource gkSprite = Manager::TextureManager::store(
                  Manager::TextureManager::load("Assets/Art/Misc/placeholder_32.png")
            );

            gkSGO.sprite().setTexture(*Manager::TextureManager::get(gkSprite));
            gkSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
            gkSGO.sprite().setScale(2, 2);
            gkSGO.middleAnchorPoint(true);

            // create vessel, pass it server vessel controller too
            new Vessel(gkSGO,cMap,12.0F,12.0F,cont,1.0F,1.0F);

            // register the vessel controller with all clients
            Message msg;
            memset(&msg,0,sizeof(msg));
            command->getGameState()->registerWithAllPlayers(cont,&msg);
        }
        else if(mode == DEITY)
        {
            //SeverDeityController* deityController = new DeityController();
            //p->setController(deityController);

            //create deity, pass it controller too.
        }
    }


}
