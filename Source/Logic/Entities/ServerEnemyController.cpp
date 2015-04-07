#include "ServerEnemyController.h"

#include "../NetworkEntityPairs.h"
#include "../Artificial Intelligence/Behaviour.h"

#include <cstdio>

ServerEnemyController::ServerEnemyController(Behaviour *behaviour)
    : ServerCommandEntity(NET_ENT_PAIR_SERVERENEMYCONTROLLER_CLIENTENEMYCONTROLLER)
     ,behaviour(behaviour)
{
}

ServerEnemyController::~ServerEnemyController()
{
}

void ServerEnemyController::init()
{
    if (behaviour)
        behaviour->init();
        
    printf("I AM TYPE: %d\r\n", type);
}

void ServerEnemyController::updateBehaviour(float deltaTime)
{
    if (behaviour)
        behaviour->update(deltaTime);
}
