#include "ClientEnemyController.h"

#include "../NetworkEntityPairs.h"

ClientEnemyController::ClientEnemyController(int id, EnemyControllerInit *initData)
    : NetworkControllerEntity(id, NET_ENT_PAIR_SERVERENEMYCONTROLLER_CLIENTENEMYCONTROLLER)
{
    // Init Data:
    // initData->type  ENEMY_TYPES
    // initData->x     float
    // initData->y     float
}

ClientEnemyController::~ClientEnemyController()
{
}

void ClientEnemyController::onUpdate( Message message )
{
    /* Respond to messages by queueing events */
    switch (message.type)
    {
        default:
            break;
    }
}
