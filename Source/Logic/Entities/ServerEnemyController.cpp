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
    static float time = 0.05;
    static int xDirection;
    static int yDirection;

    time -= deltaTime;

    if (time > 0)
      return;

    time = 0.05;

    float vessel_X;
    float vessel_Y;

    float gk_X;
    float gk_Y;

    MoveEvent *event;

    if (_servGameScene && _currEntity)
    {


      for(int i = 0; i < _servGameScene->getPlayerList().size(); i++)
      {

          gk_X = _currEntity->left;
          gk_Y = _currEntity->top;

          vessel_X = static_cast<Vessel*>(_servGameScene->getPlayerList()[i])->left;
          vessel_Y = static_cast<Vessel*>(_servGameScene->getPlayerList()[i])->top;

          std::cout << "Vessel x: " << vessel_X << std::endl;
          std::cout << "Vessel y: " << vessel_Y << std::endl;

          xDirection = 0;
          yDirection = 0;

          if (vessel_X > gk_X )
          {
            xDirection += 1;
            std::cout << "GATEKEEPER CHANGE DIRECTION RIGHT" << std::endl;
            std::cout << "GateKeeper x: " << gk_X << std::endl;
            std::cout << "GateKeeper y: " << gk_Y << std::endl;
          }
          if (vessel_X < gk_X)
          {
            xDirection -= 1;
            std::cout << "GATEKEEPER CHANGE DIRECTION LEFT" << std::endl;
            std::cout << "GateKeeper x: " << gk_X << std::endl;
            std::cout << "GateKeeper y: " << gk_Y << std::endl;
          }
          if (vessel_Y > gk_Y)
          {
            yDirection += 1;
            std::cout << "GATEKEEPER CHANGE DIRECTION DOWN" << std::endl;
            std::cout << "GateKeeper x: " << gk_X << std::endl;
            std::cout << "GateKeeper y: " << gk_Y << std::endl;
          }
          if (vessel_Y < gk_Y)
          {
            yDirection -= 1;
            std::cout << "GATEKEEPER CHANGE DIRECTION UP" << std::endl;
            std::cout << "GateKeeper x: " << gk_X << std::endl;
            std::cout << "GateKeeper y: " << gk_Y << std::endl;
          }


          event = new MoveEvent(0, 0, xDirection, yDirection, 0);
          addEvent(event);
      }

    }


    if (behaviour)
        behaviour->update(deltaTime);
}


void ServerEnemyController::setEntity(Entity* e)
{
  _currEntity = e;
}
