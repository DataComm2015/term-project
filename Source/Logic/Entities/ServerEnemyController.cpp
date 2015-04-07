/********************************************************************************
**	SOURCE FILE:	ServerEnemyController.cpp -  	Enemy server controller class
**                                              maintains and updates gatekeper behaviour on
**                                              the server.
**	PROGRAM:	Term_Project
**
**	DATE: 		February 15, 2015
**
**
**	DESIGNER: 	Calvin Rempel
**
**	PROGRAMMER: Calvin Rempel
**              Filip Gutica A00781910
**
***********************************************************************************/
#include "ServerEnemyController.h"

#include "../NetworkEntityPairs.h"
#include "../Artificial Intelligence/Behaviour.h"
#include "../Event.h"
#include "../Creature.h"

#include <cmath>

#include <cstdio>


ServerEnemyController::ServerEnemyController(Behaviour *behaviour, ServerGameScene* sgs)
    : ServerNetworkController()
    , behaviour(behaviour)
{
  moving = false;

  _servGameScene = sgs;

  attackTimer = 1;
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
    float vessel_X;
    float vessel_Y;

    float gk_X;
    float gk_Y;

    MoveEvent *event;
    AttackEvent *attackEvent;

    if (_servGameScene && _currEntity)
    {
        gk_X = _currEntity->left;
        gk_Y = _currEntity->top;

        if ((targetVessel = detectVessels()) == NULL)
        {
          if (moving)
          {
            event = new MoveEvent(gk_X, gk_Y, 0, 0, 0);
            addEvent(event);
            moving = false;
            return;
          }
          return;
        }
        else
        {
          vessel_X = targetVessel->left;
          vessel_Y = targetVessel->top;
        }

      //  std::cout << "Vessel x: " << vessel_X << std::endl;
      //  std::cout << "Vessel y: " << vessel_Y << std::endl;

        xDirection = 0;
        yDirection = 0;

        if (vessel_X > gk_X + THRESHOLD || vessel_X > gk_X - THRESHOLD)
        {
          xDirection = 1;

        }
        else
        {
          xDirection = -1;

        }

        if ((vessel_Y > gk_Y + THRESHOLD || vessel_Y > gk_Y - THRESHOLD) )
        {
          yDirection = 1;
        }
        else
        {
          yDirection = -1;

        }

        if (prevX != xDirection || prevY != yDirection)
        {
          moving = true;
          /*
          std::cout << "Adding move event" << std::endl;
          std::cout << "X Direction " << xDirection << std::endl;
          std::cout << "Y Direction " << yDirection << std::endl;
          */
          prevX = xDirection;
          prevY = yDirection;

          event = new MoveEvent(gk_X, gk_Y, xDirection, yDirection, 0);
          addEvent(event);
        }
        attackTimer -= deltaTime;

        if (attackTimer <= 0)
        {
          attackEvent = new AttackEvent(getId(), ActionType::normalAttack, targetVessel->left, targetVessel->top);

          addEvent(attackEvent);
          attackTimer = 1;
        }

    }

    if (behaviour)
    {
        behaviour->update(deltaTime);
    }
}

Vessel* ServerEnemyController::detectVessels()
{
  float x1 = _currEntity->left;
  float y1 = _currEntity->top;

  float x2, y2;
  std::vector<Vessel*> *players = _servGameScene->getPlayerList();
  int len = players->size();

  for(int i = 0; i < _servGameScene->getPlayerList()->size(); i++)
  {
    x2 = (_servGameScene->getPlayerList()->at(i))->left;
    y2 = (_servGameScene->getPlayerList()->at(i))->top;

    if (getDistance(x1, y1, x2, y2) <= _currEntity->getRange())
      return (_servGameScene->getPlayerList()->at(i));
  }

  return NULL;
}

float ServerEnemyController::getDistance(float x1, float y1, float x2, float y2 )
{
  float result;

  result = std::abs( std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2) );

  return result;
}

void ServerEnemyController::setEntity(GateKeeper* e)
{
  _currEntity = e;
}
