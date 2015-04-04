#include "ServerEnemyController.h"

#include "../NetworkEntityPairs.h"
#include "../Artificial Intelligence/Behaviour.h"
#include "../Event.h"


#include <cstdio>


ServerEnemyController::ServerEnemyController(Behaviour *behaviour, ServerGameScene* sgs)
    : ServerNetworkController()
    , behaviour(behaviour)
{
  moving = false;

  _servGameScene = sgs;
}

ServerEnemyController::~ServerEnemyController()
{
}

void ServerEnemyController::init()
{
    if (behaviour)
        behaviour->init();
}


void ServerEnemyController::updateBehaviour(float deltaTime)
{
    if (_servGameScene && _currEntity)
    {
      std::cout << "GateKeeper x: " << _currEntity->left << std::endl;
      std::cout << "GateKeeper y: " << _currEntity->top << std::endl;

      for(int i = 0; i < _servGameScene->getPlayerList().size(); i++)
      {
          std::cout << "Vessel x: " << static_cast<Vessel*>(_servGameScene->getPlayerList()[i])->left << std::endl;
          std::cout << "Vessel y: " << static_cast<Vessel*>(_servGameScene->getPlayerList()[i])->top << std::endl;

          if (!moving)
          {
            moving = true;

            MoveEvent *event = new MoveEvent(0, 0, 0, 0, 0);
            addEvent(event);
          }

      }

    }


    if (behaviour)
        behaviour->update(deltaTime);
}


void ServerEnemyController::setEntity(Entity* e)
{
  _currEntity = e;
}
