#include "ServerEnemyController.h"

#include "../NetworkEntityPairs.h"
#include "../Artificial Intelligence/Behaviour.h"
#include "../Event.h"

#include <cstdio>


ServerEnemyController::ServerEnemyController(Behaviour *behaviour)
    : ServerNetworkController()
    , behaviour(behaviour)
{
    moving = false;
}

ServerEnemyController::~ServerEnemyController()
{
}

void ServerEnemyController::init()
{
    if (behaviour)
    {
        behaviour->init();
    }
}

void ServerEnemyController::updateBehaviour(float deltaTime)
{
    /*
    if (!moving)
    {
      moving = true;

      MoveEvent *event = new MoveEvent(-1,0,-1,0,0);
      addEvent(event);
    }
    //*/

    if (behaviour)
    {
        behaviour->update(deltaTime);
    }
}
