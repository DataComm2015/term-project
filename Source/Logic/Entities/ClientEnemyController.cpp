/*#include "ClientEnemyController.h"
#include "../NetworkEntityPairs.h"
#include <iostream>

using std::cout;
using std::endl;

ClientEnemyController::ClientEnemyController(int id, EnemyControllerInit *initData, GameScene *gs)
    : ClientNetworkController(id, NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER)
{
    gameScene = gs;

    // Init Data:
    // initData->type  ENEMY_TYPES
    // initData->x     float
    // initData->y     float

    // Create the enemy
    enemy = EntityFactory::createEnemy(initData->type, this, gs->getcMap(), initData->x, initData->y);
    //cout << "Made an enemy: " << initData->type << " (" << initData->x << ", " << initData->y << ")" << endl;
}

ClientEnemyController::~ClientEnemyController()
{
}

void ClientEnemyController::onUpdate( Message message )
{
     // Respond to messages by queueing events
    switch (message.type)
    {
        default:
            break;
    }
}
*/
