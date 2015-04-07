/********************************************************************************
**	SOURCE FILE:	MiniBoss.cpp -
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
#include "MiniBoss.h"
#include "../../Event.h"
#include "../../Entities/ServerEnemyController.h"
#include <typeinfo>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace Manager;

// sound set loaded should be determined by enemy type
//static id_resource stoneWalkSoundMBoss = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_travel_01.ogg"));
//static id_resource hurtSoundMBoss 		  = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_hurt_01.ogg"));
//static id_resource attackSoundMBoss		 = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_attack_01.ogg"));

// bug fix by Sanders Lee
MiniBoss::MiniBoss(SGO& sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0) :
GateKeeper(sprite, map, x, y, ctrl, h, w)
{
    _range = 15;
    _health = 100;
    _type = 1;
    _attack = 1;
    _attackSpeed = 1;
    _xPos = x;
    _yPos = y;
    _xSpeed = 0.06;
    _ySpeed = 0.06;
    movingLeft = movingRight = movingUp = movingDown = _moving = false;

    int randDirection = (rand() % 3) - 1;

    getSprite().sprite().setScale(randDirection, 1);

    gkAnimation = new Animation(&sprite, sf::Vector2i(30, 42), 4, 8);

	/*travel_SndB = Manager::SoundManager::store(Manager::SoundManager::load("Assets/Sound/Enemies/ghost/ghost_travel_01.ogg"));
    attack_SndB = Manager::SoundManager::store(Manager::SoundManager::load("Assets/Sound/Enemies/ghost/ghost_attack_02.ogg"));
    hurt_SndB = Manager::SoundManager::store(Manager::SoundManager::load("Assets/Sound/Enemies/ghost/ghost_attack_03.ogg"));
    death_SndB = Manager::SoundManager::store(Manager::SoundManager::load("Assets/Sound/Enemies/ghost/ghost_death.ogg"));

    travel_Snd = Manager::SoundManager::play(travel_SndB, sf::Vector2f(x, y));
	attack_Snd = Manager::SoundManager::play(attack_SndB, sf::Vector2f(x, y));
	hurt_Snd = Manager::SoundManager::play(hurt_SndB, sf::Vector2f(x, y));
	death_Snd = Manager::SoundManager::play(death_SndB, sf::Vector2f(x, y));

	travel_Snd.setLoop(true);
    travel_Snd.play();*/

}

MiniBoss::~MiniBoss()
{
    footstep.stop();
}

/******************************************************************************
*   FUNCTION: onUpdate()
*
*   DATE: April 6 2014
*
*   REVISIONS: Thomas Tallentire - Added handling for Marx::SET_HEALTH Events
*              Alex Lam - Added handling for Marx::SKILL Events
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: onUpdate(float)
*
*   PARAMETERS: deltaTime   - Time this onUpdate was called
*
*   RETURNS: void
*
*   NOTES: update function for enemies. Gets called every frame of the game.
*          moves the gate keeper, deals with gettack attack, performing attacks
*          performing animations and playing sounds
******************************************************************************/
void MiniBoss::onUpdate(float deltaTime)
{
  //Perform the generic MiniBoss animation
  animate();

  //  std::cout << "MiniBoss.cpp ON UPDATE." << std::endl;
  std::vector<Marx::Event*>* eventQueue = getController()->getEvents();
  for( std::vector< Marx::Event*>::iterator it = eventQueue->begin()
      ; it != eventQueue->end()
      ; ++it )
  {

	std::cout << "MiniBoss::Event " << (*it)->type << std::endl;

    // switch on type
    switch((*it)->type)
    {
    	case ::Marx::MOVE:
  		{
    		MoveEvent* ev = (MoveEvent*) (*it);

        	processMoveEvent(ev);

    		break;
  		}
  		case ::Marx::SET_HEALTH:
  		{
			if (top != -100)
			{
	  			SetHealthEvent * event = (SetHealthEvent*)(*it);

		    	processSetHealthEvent(event);
			}
        break;
  		}
		  case ::Marx::ATTACK:
		  {
		    AttackEvent* aev = (AttackEvent*) (*it);

		    processAttackEvent(aev);

		    break;
		  }
		  case ::Marx::SKILL:
		  {
		    // process the skill event, and increase/decrease hp and stuff
		    SkillEvent *ev = (SkillEvent*)(*it);

		    processSkillEvent(ev);

		    break;
		  }
    }


  }
  getController()->clearEvents();


  Entity::rMove(newXSpeed, newYSpeed,false);

}


void MiniBoss::processMoveEvent(MoveEvent* ev)
{
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

  playSound(newXSpeed, newYSpeed);
}

void MiniBoss::processSkillEvent(SkillEvent* ev)
{
  printf("MiniBoss BEFORE Health: %d\n", _health);
  switch(ev->getSkillType())
  {
      case SKILLTYPE::HEAL:
          _health += ev->getValue();
      break;
      case SKILLTYPE::DMG:
          _health -= ev->getValue();
      break;
      case SKILLTYPE::BUFF:
          _xSpeed += ev->getValue();
          _ySpeed += ev->getValue();
      break;
      case SKILLTYPE::DEBUFF:
          _xSpeed -= ev->getValue();
          _ySpeed -= ev->getValue();
      break;
  }

  printf("MiniBoss AFTER Health: %d\n", _health);

  if(_health <= 0)
  {
    std::cout << "Moving MiniBoss to ambiguous destination!!" << std::endl;
    onDestroy();
  }
}
void MiniBoss::processSetHealthEvent(SetHealthEvent* ev)
{
  _health = getHealth()-ev->getChange();

  Controller * cont = dynamic_cast<Controller*>(NetworkEntityMultiplexer::getInstance()->getEntityById(ev->getEntId()));
  AddPointsEvent *pointsEvent = new AddPointsEvent(ev->getChange());
  cont->addEvent(pointsEvent);

  if(_health <= 0)
  {
    std::cout << "MiniBoss Dead" << std::endl;
    onDestroy();
  }
}
void MiniBoss::processAttackEvent(AttackEvent* aev)
{
  std::cout << "ATTACK" << std::endl;
  createAttack(*aev, getSprite(), left, top);
}

void MiniBoss::playSound(float xSpeed, float ySpeed)
{
  /*soundActive = false;
  steppedTile = GRASS;

  // Sounds for walking:
  // first get the tile type we're walking on
  Cell* footstepTile = *getCell().begin();
  sf::Vector2f soundPos(left, top);
    footstep.setPosition(left + newXSpeed, top + newYSpeed, 0);  // this line prevent's MiniBoss's
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
      footstep = SoundManager::play(grassWalkSoundMBoss, soundPos);
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
      footstep = SoundManager::play(stoneWalkSoundMBoss, soundPos);
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

void MiniBoss::animate()
{
  if (isMoving())
    gkAnimation->step(1);
}

bool MiniBoss::isMoving()
{
  return (movingLeft || movingRight || movingUp || movingDown);
}

void MiniBoss::setRange(int r)
{
  _range = r;
}

void MiniBoss::setHealth(int h)
{
  _health = h;
}

void MiniBoss::setAttack(int a)
{
  _attack = a;
}

void MiniBoss::setAttackSpeed(float as)
{
  _attackSpeed == as;
}


void MiniBoss::setXSpeed(float x)
{
  _xSpeed = x;
}

void MiniBoss::setYSpeed(float y)
{
  _ySpeed = y;
}

void MiniBoss::setSpeed(int _speed)
{
    _xSpeed = _speed;
    _ySpeed = _speed;
}

float MiniBoss::getXSpeed()
{
	return _xSpeed;
}

float MiniBoss::getYSpeed()
{
	return _ySpeed;
}

int MiniBoss::getSpeed()
{
	return _xSpeed;
}

int MiniBoss::getRange()
{
  return _range;
}

int MiniBoss::getHealth()
{
  return _health;
}

int MiniBoss::getAttack()
{
  return _attack;
}

float MiniBoss::getAttackSpeed()
{
  return _attackSpeed;
}



void MiniBoss::turn()
{

}

void MiniBoss::onCreate()
{

}

void MiniBoss::stopAllSounds()
{
    footstep.stop();
}

bool MiniBoss::operator==(const VEntity&)
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
Entity *MiniBoss::getEntity()
{
    return this;
}
