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
#include <cstdlib>

using namespace Manager;

Animation *gkAnimation;

// bug fix by Sanders Lee
GateKeeper::GateKeeper(SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0) :
VEntity(sprite, map, x, y, ctrl, h, w)
{
    _range = 10;
    _health = 100;
    _type = 1;
    _attack = 1;
    _attackSpeed = 1;
    _xPos = x;
    _yPos = y;
    _xSpeed = 0.06;
    _ySpeed = 0.06;
    movingLeft = movingRight = movingUp = movingDown = _moving = false;
    soundActive = false;

    srand (time(NULL));

    int randDirection = (rand() % 3) - 1;

    _sprite = &sprite;

    _sprite->sprite().setScale(randDirection, 1);

    gkAnimation = new Animation(_sprite, sf::Vector2i(40, 40), 16, 7);
}

GateKeeper::~GateKeeper()
{

}

/***
-- PROGRAMMER:  Filip Gutica
--				Sanders Lee (Debugged synchronization problem across clients,
--                           Added sound for GateKeeper travel)
***/
void GateKeeper::onUpdate(float deltaTime)
{
  //Perform the generic gatekeeper animation
  gkAnimation->step(1);

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
      {
    		MoveEvent* ev = (MoveEvent*) (*it);
        int xDir = ev->getXDir();
        int yDir = ev->getYDir();

        Entity::aMove(ev->getX(), ev->getY(), false);

        if (yDir < 0)
        {
          newYSpeed = -_ySpeed;
          int randDirection = (rand() % 3) - 1;
          _sprite->sprite().setScale(randDirection, 1);
          movingUp = true;
          movingDown = false;
        }
        else
        {
          newYSpeed = _ySpeed;
          int randDirection = (rand() % 3) - 1;
          _sprite->sprite().setScale(randDirection, 1);
          movingDown = true;
          movingUp = false;
        }

        if (xDir > 0)
        {
          newXSpeed = _xSpeed;
          _sprite->sprite().setScale(1, 1);
          movingRight = true;
          movingLeft = false;
        }
        else
        {
          newXSpeed = -_xSpeed;
          _sprite->sprite().setScale(-1, 1);
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

    		break;
      }
    }

    playSound(newXSpeed, newYSpeed);

  }
  getController()->clearEvents();


  if (isMoving())
    Entity::rMove(newXSpeed, newYSpeed, false);

}

void GateKeeper::playSound(float xSpeed, float ySpeed)
{
  BlockZone steppedTile = GRASS;
  grassWalkSound = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_travel_01.ogg"));
  stoneWalkSound = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_travel_01.ogg"));
  hurtSound = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_hurt_01.ogg"));
  attackSound = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_attack_01.ogg"));

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
      footstep = SoundManager::play(grassWalkSound, soundPos);
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
      footstep = SoundManager::play(stoneWalkSound, soundPos);
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

void GateKeeper::animate()
{

}

bool GateKeeper::isMoving()
{
  return (movingLeft || movingRight || movingUp || movingDown);
}

void GateKeeper::setRange(int r)
{
  _range = r;
}

void GateKeeper::setHealth(int h)
{
  _health = h;
}

void GateKeeper::setAttack(int a)
{
  _attack = a;
}

void GateKeeper::setAttackSpeed(int as)
{
  _attackSpeed == as;
}


void GateKeeper::setXSpeed(float x)
{
  _xSpeed = x;
}

void GateKeeper::setYSpeed(float y)
{
  _ySpeed = y;
}

void GateKeeper::setSpeed(int _speed)
{
    _xSpeed = _speed;
    _ySpeed = _speed;
}

int GateKeeper::getSpeed()
{
	return _xSpeed;
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
