/********************************************************************************
**	SOURCE FILE:	GateKeeper.cpp -  	GateKeeper class implementation. Parent class
**                                    for the enemies.
**
**	PROGRAM:	Term_Project
**
**	DATE: 		February 15, 2015
**
**
**	DESIGNER: 	Filip Gutica A00781910
**
**	PROGRAMMER: Filip Gutica A00781910
**
***********************************************************************************/
#include "GateKeeper.h"
#include "../../Event.h"
#include "../../Entities/ServerEnemyController.h"
#include <typeinfo>
#include <iostream>

GateKeeper::GateKeeper(SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0) :
  VEntity(sprite, map, x, y, ctrl, h, w)
//  _ctrl(ctrl)
  {
    _range = 1;
    _health = 100;
    _type = 1;
    _attack = 1;
    _attackSpeed = 1;
    _movementSpeed = 1;
    _incombat = false;
    _cooldown = 1;
    _xPos = x;
    _yPos = y;
    _xSpeed = 0.01;
    _ySpeed = 0.01;
    _moving = false;

  };

GateKeeper::~GateKeeper()
{

}

void GateKeeper::onUpdate()
{
  static float newXSpeed = 0;
  static float newYSpeed = 0;

  std::cout << "GateKeeper.cpp ON UPDATE." << std::endl;

std::vector<Marx::Event*>* eventQueue = getController()->getEvents();
for( std::vector< Marx::Event*>::iterator it = eventQueue->begin()
  ; it != eventQueue->end()
  ; ++it )
{

  // switch on type
  switch((*it)->type)
  {
    case ::Marx::MOVE:
        MoveEvent* ev = (MoveEvent*) (*it);
        int xDir = ev->getXDir();
        int yDir = ev->getYDir();

        if (yDir == -1)
        {
          newYSpeed -= _ySpeed;
          std::cout << "GateKeeper.cpp: moving up" << std::endl;
        }
        else if (yDir == 1)
        {
          newYSpeed += _ySpeed;
          std::cout << "GateKeeper.cpp: moving down" << std::endl;
        }
        else if (xDir == 1)
        {
          newXSpeed += _xSpeed;
          std::cout << "GateKeeper.cpp: moving right" << std::endl;
        }
        else if (xDir == -1)
        {
          newXSpeed -= _xSpeed;
          std::cout << "GateKeeper.cpp: moving left" << std::endl;
        }


        break;
  }
}
getController()->clearEvents();

// if (movingLeft)
//       newXSpeed = -xSpeed;
//   else if (movingRight)
//       newXSpeed = xSpeed;
//
//   if (movingUp)
//       newYSpeed = -ySpeed;
//   else if (movingDown)
//       newYSpeed = ySpeed;


  Entity::rMove(newXSpeed, newYSpeed,false);
}

bool GateKeeper::isMoving()
{
  return (movingLeft || movingRight || movingUp || movingDown);
}

void GateKeeper::detectPlayers()
{

}

void GateKeeper::enterCombat()
{

}

void GateKeeper::leaveCombat()
{

}

bool GateKeeper::inCombatRange()
{
  return true;
}

void GateKeeper::setRange(int r)
{

}

void GateKeeper::setHealth(int h)
{

}

void GateKeeper::setAttack(int as)
{

}

void GateKeeper::setAttackSpeed(int as)
{

}

void GateKeeper::setMovementSPed(int ms)
{

}

void GateKeeper::setTarget(/*Player*/)
{

}

void GateKeeper::setCooldown(/*Timer*/)
{

}

void GateKeeper::setPosition(float x, float y)
{

}

void GateKeeper::setXSpeed(float x)
{

}

void GateKeeper::setYSpeed(float y)
{

}

int GateKeeper::getRange()
{
  return _range;
}

int GateKeeper::getHealth()
{
  return _health;
}

int GateKeeper::getAttack()
{
  return _attack;
}

int GateKeeper::getAttackSpeed()
{
  return _attackSpeed;
}

int GateKeeper::getMovementSpeed()
{
  return _movementSpeed;
}
//virtual Vessel getTarget();
time_t GateKeeper::getCooldown()
{
  return _cooldown;
}

void GateKeeper::turn()
{

}

void GateKeeper::onCreate()
{

}

void GateKeeper::onDestroy()
{

}

bool GateKeeper::operator==(const VEntity&)
{
  return true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getEntity
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Calvin Rempel
--
-- PROGRAMMER:	Calvin Rempel
--
-- INTERFACE: Entity *getEntity()
--
-- RETURNS: The Entity associated with the Creature
--
-- NOTES:
-- This function provides a method for retrieving the Entity from the Creature.
----------------------------------------------------------------------------------------------------------------------*/
Entity *GateKeeper::getEntity()
{
    return this;
}
