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


          xDirection = 0;
          yDirection = 0;

          if (vessel_X > gk_X )
          {
            xDirection += 1;
          }
          if (vessel_X < gk_X)
          {
            xDirection -= 1;
          }
          if (vessel_Y > gk_Y)
          {
            yDirection += 1;
          }
          if (vessel_Y < gk_Y)
          {
            yDirection -= 1;
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
