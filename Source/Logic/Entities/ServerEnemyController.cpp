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
**              Filip Gutica
**
**	PROGRAMMER: Calvin Rempel
**              Filip Gutica
**
***********************************************************************************/
#include "ServerEnemyController.h"

#include "../NetworkEntityPairs.h"
#include "../Artificial Intelligence/Behaviour.h"
#include "../Event.h"
#include "../Creature.h"

#include <cmath>

#include <cstdio>

/******************************************************************************
*   FUNCTION: ServerEnemyController() Constructor
*
*   DATE: April 6 2014
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER:   Calvin Rempel
*
*   PROGRAMMER: Calvin Rempel
*               Filip Gutica
*
*   INTERFACE: Minion(Behaviour*, ServergameScene*)
*
*   PARAMETERS: behaviour   - Behaviour for this enemy controller
*               sgs         - Pointer to the server game scene
*
*   RETURNS: void
*
*   NOTES: Constructor for the server enemy controller initializes the enemy to not
*          be moving, initilizes the server game scene, and sets the enemy attack timer
******************************************************************************/
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

/******************************************************************************
*   FUNCTION: init
*
*   DATE: April 6 2014
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER:   Calvin Rempel
*
*   PROGRAMMER: Calvin Rempel
*
*   INTERFACE: init()
*
*   PARAMETERS: void
*
*   RETURNS: void
*
*   NOTES: Initializes the behaviour
******************************************************************************/
void ServerEnemyController::init()
{
    if (behaviour)
    {
        behaviour->init();
    }
}

/******************************************************************************
*   FUNCTION: updateBehaviour
*
*   DATE: April 6 2014
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER:  Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: updateBehaviour(float deltatime)
*
*   PARAMETERS: deltatime   - Time amount of time since the last update behaviour call
*
*   RETURNS: void
*
*   NOTES: Updates the behaviour of the enemy. This is where all of the AI logic
*          resides. The enemy scans for near by players and when a player enters the
*          gatekeeper's range, the gate keeper will begin following the player and attackin
*          the player until the player either kills the enemy or moves out of the enemy's
*          range.
******************************************************************************/
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

          prevX = xDirection;
          prevY = yDirection;

          event = new MoveEvent(gk_X, gk_Y, xDirection, yDirection, 0);
          addEvent(event);
        }
        attackTimer -= deltaTime;

        // Attack every tick of attackTimer
        if (attackTimer <= 0)
        {
          attackEvent = new AttackEvent(getId(), ActionType::normalAttack, targetVessel->left - gk_X, targetVessel->top - gk_Y);

          addEvent(attackEvent);
          attackTimer = 1;
        }

    }

    if (behaviour)
    {
        behaviour->update(deltaTime);
    }
}

/******************************************************************************
*   FUNCTION: detectVessels
*
*   DATE: April 6 2014
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER:  Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: detectVessels()
*
*   PARAMETERS: void
*
*   RETURNS: Vessel*  - The vessel detected within this enemy's range
*
*   NOTES: Checks the coordinates of every player in the game against the enemy's
*          current position. If a vessel is detected, the detected vessel is returned.
******************************************************************************/
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

/******************************************************************************
*   FUNCTION: getDistance
*
*   DATE: April 6 2014
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER:  Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: getDistance(float x1, float y1, float x2, float y2)
*
*   PARAMETERS: x1  - x coordinate of the first point
*               y1  - y coordinate of the first point
*               x2  - x coordinate of the second point
*               y2  - y coordinate of the second point
*
*   RETURNS: float  - Distance between the two coordinates passed
*
*   NOTES: Returns the distance between the two points provided
******************************************************************************/
float ServerEnemyController::getDistance(float x1, float y1, float x2, float y2 )
{
  float result;

  result = std::abs( std::pow((x2 - x1), 2) + std::pow((y2 - y1), 2) );

  return result;
}

/******************************************************************************
*   FUNCTION: setEntity
*
*   DATE: April 6 2014
*
*   REVISIONS: (Date and Description)
*
*   DESIGNER:  Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: setEntity(GateKeeper* e)
*
*   PARAMETERS: e   - Means of passing the controlled entity to this controller
*
*   RETURNS: void
*
*   NOTES: Sets the entity controlled by this conroller
******************************************************************************/
void ServerEnemyController::setEntity(GateKeeper* e)
{
  _currEntity = e;
}
