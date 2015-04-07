/********************************************************************************
**	SOURCE FILE:	MiniBee.cpp -
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
#include "MiniBee.h"
#include "../../Event.h"
#include "../../Entities/ServerEnemyController.h"
#include <typeinfo>
#include <iostream>
#include <cstdlib>

using namespace Manager;

// sound set loaded should be determined by enemy type
//static id_resource grassWalkSoundMiniBee = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_travel_01.ogg"));
//static id_resource stoneWalkSoundMiniBee = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_travel_01.ogg"));
//static id_resource hurtSoundMiniBee 			= SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_hurt_01.ogg"));
//static id_resource attackSoundMiniBee		= SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_attack_01.ogg"));

// bug fix by Sanders Lee
MiniBee::MiniBee(SGO& sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0) :
GateKeeper(sprite, map, x, y, ctrl, h, w)
{
    _range = 10;
    _health = 100;
    _type = 1;
    _attack = 1;
    _attackSpeed = 1;
    _xPos = x;
    _yPos = y;
    _xSpeed = 0.03;
    _ySpeed = 0.03;
    movingLeft = movingRight = movingUp = movingDown = _moving = false;


    int randDirection = (rand() % 3) - 1;

    getSprite().sprite().setScale(randDirection, 1);

    gkAnimation = new Animation(&sprite, sf::Vector2i(16, 16), 16, 7);

}

MiniBee::~MiniBee()
{
    footstep.stop();
}

/***
-- PROGRAMMER:  Filip Gutica
--				Sanders Lee (Debugged synchronization problem across clients,
--                           Added sound for GateKeeper travel)
***/
void MiniBee::onUpdate(float deltaTime)
{
  //Perform the generic gatekeeper animation
  animate();

  //  std::cout << "GateKeeper.cpp ON UPDATE." << std::endl;
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

        Entity::aMove(ev->getX(), ev->getY(), false);

        if (yDir < 0)
        {
          newYSpeed = -_ySpeed;
          int randDirection = (rand() % 3) - 1;
          getSprite().sprite().setScale(randDirection, 1);
          movingUp = true;
          movingDown = false;
        }
        else
        {
          newYSpeed = _ySpeed;
          int randDirection = (rand() % 3) - 1;
          getSprite().sprite().setScale(randDirection, 1);
          movingDown = true;
          movingUp = false;
        }

        if (xDir > 0)
        {
          newXSpeed = _xSpeed;
          getSprite().sprite().setScale(1, 1);
          movingRight = true;
          movingLeft = false;
        }
        else
        {
          newXSpeed = -_xSpeed;
          getSprite().sprite().setScale(-1, 1);
          movingLeft = true;
          movingRight = false;
        }

        if (xDir == 0)
        {
          newXSpeed = 0;
          movingLeft = false;
          movingRight = false;
        }

        if (yDir == 0)
        {
          newYSpeed = 0;
          movingUp = false;
          movingDown = false;
        }

        //playSound(newXSpeed, newYSpeed);

    		break;
    }


  }
  getController()->clearEvents();




  Entity::rMove(newXSpeed, newYSpeed,false);


}

void MiniBee::playSound(float xSpeed, float ySpeed)
{
  /*soundActive = false;
  steppedTile = GRASS;

  // Sounds for walking:
  // first get the tile type we're walking on
  Cell* footstepTile = *getCell().begin();
  sf::Vector2f soundPos(left, top);
    footstep.setPosition(left + newXSpeed, top + newYSpeed, 0);  // this line prevent's GateKeeper's
                                  // footsteps from fading & being off-center
    footstep.setMinDistance(3.0);

  if (footstepTile->getTileId() >= GRASS_TL && footstepTile->getTileId() <= GRASS_BR)
  {
    // we need the extra soundActive boolean to make sure we're not playing a new
    // sound when there's already a walking sound active for our vessel
    if (((xSpeed != 0 || ySpeed != 0) && !soundActive) ||
      (soundActive && steppedTile != GRASS))
    {
      footstep.stop();
      footstep = SoundManager::play(grassWalkSoundMiniBee, soundPos);
      footstep.setLoop(true);
      footstep.play();
      soundActive = true;
      steppedTile = GRASS;
    }
  }
  else if (footstepTile->getTileId() >= STONE_TL && footstepTile->getTileId() <= ARBITER_BR)
  {
    if (((xSpeed != 0 || ySpeed != 0) && !soundActive) ||
      (soundActive && steppedTile != STONE))
    {
      footstep.stop();
      footstep = SoundManager::play(stoneWalkSoundMiniBee, soundPos);
      footstep.setLoop(true);
      footstep.play();
      soundActive = true;
      steppedTile = STONE;
    }
  }
    // stop all sounds of walking if travelling speed is (0, 0)
  if ((xSpeed == 0 && ySpeed == 0) && soundActive)
  {
    footstep.stop();
    soundActive = false;
  }//*/
}

void MiniBee::animate()
{
  if (isMoving())
    gkAnimation->step(1);
  else
    gkAnimation->step(5);
}

bool MiniBee::isMoving()
{
  return (movingLeft || movingRight || movingUp || movingDown);
}

void MiniBee::setRange(int r)
{
  _range = r;
}

void MiniBee::setHealth(int h)
{
  _health = h;
}

void MiniBee::setAttack(int a)
{
  _attack = a;
}

void MiniBee::setAttackSpeed(int as)
{
  _attackSpeed == as;
}


void MiniBee::setXSpeed(float x)
{
  _xSpeed = x;
}

void MiniBee::setYSpeed(float y)
{
  _ySpeed = y;
}

void MiniBee::setSpeed(int _speed)
{
    _xSpeed = _speed;
    _ySpeed = _speed;
}

int MiniBee::getSpeed()
{
	return _xSpeed;
}

int MiniBee::getRange()
{
  return _range;
}

int MiniBee::getHealth()
{
  return _health;
}

int MiniBee::getAttack()
{
  return _attack;
}

int MiniBee::getAttackSpeed()
{
  return _attackSpeed;
}

int MiniBee::getMovementSpeed()
{
  return _movementSpeed;
}

void MiniBee::turn()
{

}

void MiniBee::onCreate()
{

}

void MiniBee::onDestroy()
{

}

void MiniBee::stopAllSounds()
{
    footstep.stop();
}

bool MiniBee::operator==(const VEntity&)
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
Entity *MiniBee::getEntity()
{
    return this;
}
