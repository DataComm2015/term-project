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
#include "../../Event.h"
#include "../../Entities/ServerEnemyController.h"
#include <typeinfo>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "MiniBee.h"

using namespace Manager;

// sound set loaded should be determined by enemy type
static id_resource grassWalkSoundMiniBee = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_travel_01.ogg"));
static id_resource stoneWalkSoundMiniBee = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_travel_02.ogg"));
static id_resource hurtSoundMiniBee 	 = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_hurt_01.ogg"));
static id_resource attackSoundMiniBee	 = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_attack_01.ogg"));

id_resource beeShadow;


// bug fix by Sanders Lee
MiniBee::MiniBee(SGO& sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0) :
GateKeeper(sprite, map, x, y, ctrl, h, w)
{
    _range = 20;
    _health = 50;
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

    gkAnimation = new Animation(&sprite, sf::Vector2i(16, 16), 16, 3);

    // Load shadow texture
    beeShadow = Manager::TextureManager::store(
        Manager::TextureManager::load("Assets/Art/Shadows/bug_shadow.png")
    );

    shadow.sprite().setTexture(*Manager::TextureManager::get(beeShadow));
    shadow.sprite().setTextureRect(sf::IntRect(0, 0, 8, 3));

    this->add(shadow);
    shadow.sprite().setOrigin(-4, -17);

	/*travel_SndB = Manager::SoundManager::store(Manager::SoundManager::load("Assets/Sound/Enemies/bee/babby/bee_travel_02_baby.ogg"));
    attack_SndB = Manager::SoundManager::store(Manager::SoundManager::load("Assets/Sound/Enemies/bee/babby/bee_attack_01_baby.ogg"));
    hurt_SndB = Manager::SoundManager::store(Manager::SoundManager::load("Assets/Sound/Enemies/bee/babby/bee_hurt_02_baby.ogg"));
    death_SndB = Manager::SoundManager::store(Manager::SoundManager::load("Assets/Sound/Enemies/bee/babby/bee_death_01_baby.ogg"));

    travel_Snd = Manager::SoundManager::play(travel_SndB, sf::Vector2f(x, y));
	attack_Snd = Manager::SoundManager::play(attack_SndB, sf::Vector2f(x, y));
	hurt_Snd = Manager::SoundManager::play(hurt_SndB, sf::Vector2f(x, y));
	death_Snd = Manager::SoundManager::play(death_SndB, sf::Vector2f(x, y));

	travel_Snd.setLoop(true);
    travel_Snd.play();*/
}

MiniBee::~MiniBee()
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
void MiniBee::onUpdate(float deltaTime)
{
  //Perform the generic MiniBee animation
  animate();

  //  std::cout << "MiniBee.cpp ON UPDATE." << std::endl;
  std::vector<Marx::Event*>* eventQueue = getController()->getEvents();
  for( std::vector< Marx::Event*>::iterator it = eventQueue->begin()
      ; it != eventQueue->end()
      ; ++it )
  {

	std::cout << "MiniBee::Event " << (*it)->type << std::endl;

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


void MiniBee::processMoveEvent(MoveEvent* ev)
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

  playTravelSound(newXSpeed, newYSpeed);
}

void MiniBee::processSkillEvent(SkillEvent* ev)
{
  printf("MiniBee BEFORE Health: %d\n", _health);
  switch(ev->getSkillType())
  {
      case SKILLTYPE::HEAL:
          _health += ev->getValue();
      break;
      case SKILLTYPE::DMG:
          _health -= ev->getValue();
          playHurtSound();
      break;
      case SKILLTYPE::BUFF:
          _xSpeed += ev->getValue();
          _ySpeed += ev->getValue();
      break;
      case SKILLTYPE::DEBUFF:
          _xSpeed -= ev->getValue();
          _ySpeed -= ev->getValue();
      break;
      case SKILLTYPE::BIGHEAL:
          _health += ev->getValue();
      break;
      case SKILLTYPE::SPAWN:
          // Vessel implementation not needed
      break;
  }

  printf("MiniBee AFTER Health: %d\n", _health);

  if(_health <= 0)
  {
    std::cout << "Moving MiniBee to ambiguous destination!!" << std::endl;
    onDestroy();
  }
}
void MiniBee::processSetHealthEvent(SetHealthEvent* ev)
{
  _health = getHealth() - ev->getChange();
  playHurtSound();
  
  Controller * cont = dynamic_cast<Controller*>(NetworkEntityMultiplexer::getInstance()->getEntityById(ev->getEntId()));
  AddPointsEvent *pointsEvent = new AddPointsEvent(ev->getChange());
  cont->addEvent(pointsEvent);

  if(_health <= 0)
  {
    std::cout << "MiniBee Dead" << std::endl;
    onDestroy();
  }
}

void MiniBee::processAttackEvent(AttackEvent* aev)
{
  std::cout << "ATTACK" << std::endl;
  createAttack(*aev, getSprite(), left, top);
  playAttackSound();
}

void MiniBee::playTravelSound(float xSpeed, float ySpeed)
{
  soundActive = false;
  steppedTile = GRASS;

  // Sounds for walking:
  // first get the tile type we're walking on
  Cell* footstepTile = *getCell().begin();
  sf::Vector2f soundPos(left, top);
  footstep.setPosition(left + newXSpeed, top + newYSpeed, 0);  // this line prevent's MiniBee's
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

void MiniBee::playHurtSound()
{
    sf::Vector2f soundPos(left + newXSpeed, top + newYSpeed);
	voice.setPosition(left + newXSpeed, top + newYSpeed, 0);  // this line prevent's enemy's
															  // voice from fading & being off-center
	voice.setMinDistance(3.0);
	voice = SoundManager::play(hurtSoundMiniBee, soundPos);
	voice.play();
}

void MiniBee::playAttackSound()
{
    sf::Vector2f soundPos(left + newXSpeed, top + newYSpeed);
	voice.setPosition(left + newXSpeed, top + newYSpeed, 0);  // this line prevent's enemy's
															  // voice from fading & being off-center
	voice.setMinDistance(3.0);
	voice = SoundManager::play(attackSoundMiniBee, soundPos);
	voice.play();
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

void MiniBee::setAttackSpeed(float as)
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

float MiniBee::getXSpeed()
{
	return _xSpeed;
}

float MiniBee::getYSpeed()
{
	return _ySpeed;
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

float MiniBee::getAttackSpeed()
{
  return _attackSpeed;
}


void MiniBee::turn()
{

}

void MiniBee::onCreate()
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
