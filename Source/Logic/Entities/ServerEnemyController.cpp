/********************************************************************************
**	SOURCE FILE:	ServerEnemyController.cpp -  	GateKeeper server class controller class
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

#include <cmath>

#include <cstdio>


ServerEnemyController::ServerEnemyController(Behaviour *behaviour, ServerGameScene* sgs)
    : ServerNetworkController()
    , behaviour(behaviour)
{
  moving = false;

  _servGameScene = sgs;

  prevX = 0;
  prevY = 0;
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

    xDirection = 0;
    yDirection = 0;

    MoveEvent *event;

    if (_servGameScene && _currEntity)
    {
        gk_X = _currEntity->left;
        gk_Y = _currEntity->top;

        //Check for nearby vessels
        if ((targetVessel = detectVessels()) == NULL)
        {
          if (moving)
          {
            //Stop the gatekeeper if moving, and vessel is out of range
            event = new MoveEvent(gk_X, gk_Y, 0, 0, 0);
            addEvent(event);
            moving = false;
            return;
          }
          return;
        }
        else  // Set target x and y
        {
          vessel_X = targetVessel->left;
          vessel_Y = targetVessel->top;
        }

        //If vessel is to the Right
        if (vessel_X > gk_X + THRESHOLD || vessel_X > gk_X - THRESHOLD)
        {
          xDirection = 1;

        }
        //If vessel is to the Left
        else
        {
          xDirection = -1;

        }

        //If vessel is below
        if ((vessel_Y > gk_Y + THRESHOLD || vessel_Y > gk_Y - THRESHOLD) )
        {
          yDirection = 1;
        }
        //If vessel is above
        else
        {
          yDirection = -1;

        }

        /**
        * if only send move events if the previous direction the gate keeper was moving in
        * is not the same direction in which we want the gate keeper to move in now.
        **/
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

    if (getDistance(x1, y1, x2, y2) <= AGGRO_RADIUS)
    {
      return (_servGameScene->getPlayerList()->at(i));
    }
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
