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
**              Chris Klassen
**              Lewis Scott
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

const char *MiniBoss::travelSnds[3] = {"Assets/Sound/Enemies/ghost/ghost_travel_01.ogg",
                                        "Assets/Sound/Enemies/ghost/ghost_travel_02.ogg",
                                        "Assets/Sound/Enemies/ghost/ghost_travel_03.ogg"};

const char *MiniBoss::attackSnds[5] = {"Assets/Sound/Enemies/ghost/ghost_attack_01.ogg",
                                        "Assets/Sound/Enemies/ghost/ghost_attack_02.ogg",
                                        "Assets/Sound/Enemies/ghost/ghost_attack_03.ogg",
                                        "Assets/Sound/Enemies/ghost/ghost_attack_04.ogg",
                                        "Assets/Sound/Enemies/ghost/ghost_attack_05.ogg"};

const char *MiniBoss::hurtSnds[4] = {"Assets/Sound/Enemies/ghost/ghost_attack_06.ogg",
                                      "Assets/Sound/Enemies/ghost/ghost_attack_07.ogg",
                                      "Assets/Sound/Enemies/ghost/ghost_attack_08.ogg",
                                      "Assets/Sound/Enemies/ghost/ghost_attack_09.ogg"};


/******************************************************************************
*   FUNCTION: MiniBoss() Constructor
*
*   DATE: April 6 2014
*
*   REVISIONS:
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*               Chris Klassen
*               Lewis Scott
*
*   INTERFACE: GateKeeper(SGO&, Map*, float, float, Controller, float, float)
*
*   PARAMETERS: sprite  - Sprite for this enemy
*               map     - Pointer to the map this enemy resides on
*               x       - x coordinate
*               y       - y coordinate
*               ctrl    - pointer to the controller controlling this enemy
*               h       - height
*               w       - width
*
*   RETURNS: void
*
*   NOTES: Constructor for Mini bosses. Initializes the mini boss sets attributes
*          Sets animation.
******************************************************************************/
MiniBoss::MiniBoss(SGO& sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0) :
GateKeeper(sprite, map, x, y, ctrl, h, w)
{
    _range = 15;
    _health = 150;
    _type = 1;
    _attack = 1;
    _attackSpeed = 1;
    _xPos = x;
    _yPos = y;
    _xSpeed = 0.05;
    _ySpeed = 0.05;
    movingLeft = movingRight = movingUp = movingDown = _moving = false;

    int randDirection = (rand() % 3) - 1;

    getSprite().sprite().setScale(randDirection, 1);

    gkAnimation = new Animation(&sprite, sf::Vector2i(30, 42), 4, 8);

    grassWalkSoundMBoss = SoundManager::store(SoundManager::load(MiniBoss::travelSnds[rand() % 3]));
    stoneWalkSoundMBoss = SoundManager::store(SoundManager::load(MiniBoss::travelSnds[rand() % 3]));
    hurtSoundMBoss      = SoundManager::store(SoundManager::load(MiniBoss::hurtSnds[rand() % 4]));
    attackSoundMBoss    = SoundManager::store(SoundManager::load(MiniBoss::attackSnds[rand() % 5]));

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

/******************************************************************************
*   FUNCTION: processMoveEvent
*
*   DATE: April 6 2014
*
*   REVISIONS:
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: processMoveEvent(MoveEvent* ev)
*
*   PARAMETERS: ev   - Event to be processed
*
*   RETURNS: void
*
*   NOTES: Processes move events generated by the server enemy controller.
*   Moves this entity
******************************************************************************/
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

  playTravelSound(newXSpeed, newYSpeed);
}

/******************************************************************************
*   FUNCTION: processSkillEvent
*
*   DATE: April 6 2014
*
*   REVISIONS: Filip Gutica   - Created seperate function
*
*   DESIGNER:   Alex Lam
*               Julian Brandrick
*
*   PROGRAMMER: Alex Lam
*               Julian Brandrick
*               Sanders Lee (Inserted sound effect)
*
*   INTERFACE: processSkillEvent(SkillEvent* ev)
*
*   PARAMETERS: ev   - Event to be processed
*
*   RETURNS: void
*
*   NOTES: Processes move events generated by the server enemy controller.
*   Moves this entity
******************************************************************************/
void MiniBoss::processSkillEvent(SkillEvent* ev)
{
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

  if(_health <= 0)
  {
    onDestroy();
  }
}

/******************************************************************************
*   FUNCTION: processSetHealthEvent
*
*   DATE: April 6 2014
*
*   REVISIONS:  Filip Gutica    - Made seperate function
*
*   DESIGNER:   Thomas Tallentire
*
*   PROGRAMMER: Thomas Tallentire
*               Sanders Lee (Inserted sound effect)
*
*   INTERFACE: processSetHealthEvent(SetHealthEvent* ev)
*
*   PARAMETERS: ev   - Event to be processed
*
*   RETURNS: void
*
*   NOTES: Processes set health events generated by the server enemy controller.
*   Moves this entity
******************************************************************************/
void MiniBoss::processSetHealthEvent(SetHealthEvent* ev)
{
  _health = getHealth() - ev->getChange();
  playHurtSound();

  Controller * cont = dynamic_cast<Controller*>(NetworkEntityMultiplexer::getInstance()->getEntityById(ev->getEntId()));
  AddPointsEvent *pointsEvent = new AddPointsEvent(ev->getChange());
  cont->addEvent(pointsEvent);

  if(_health <= 0)
  {
    onDestroy();
  }
}

/******************************************************************************
*   FUNCTION: processAttackEvent
*
*   DATE: April 6 2014
*
*   REVISIONS:  Filip Gutica    - Made seperate function
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*               Sanders Lee (Inserted sound effect)
*
*   INTERFACE: processAttackEvent(AttackEvent* ev)
*
*   PARAMETERS: ev   - Event to be processed
*
*   RETURNS: void
*
*   NOTES: Proces attack events. Generate attacks
******************************************************************************/
void MiniBoss::processAttackEvent(AttackEvent* aev)
{
  createAttack(*aev, getSprite(), left, top);
  playAttackSound();
}

/******************************************************************************
*   FUNCTION: playTravelSound()
*
*   DATE: April 6 2014
*
*   REVISIONS: Filip Gutica    - Moved from on update to seperate function
*
*   DESIGNER:   Sanders Lee
*
*   PROGRAMMER: Sanders Lee
*
*   INTERFACE: playTravelSound(float, float)
*
*   PARAMETERS: xSpeed   - Horizontal speed
*               ySpeed   - Vertical speed
*
*   RETURNS: void
*
*   NOTES: Plays travelling sound associated with this enemy
******************************************************************************/
void MiniBoss::playTravelSound(float xSpeed, float ySpeed)
{
  soundActive = false;
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

/******************************************************************************
*   FUNCTION: playHurtSound()
*
*   DATE: April 6 2014
*
*   REVISIONS: Filip Gutica    - Moved from on update to seperate function
*
*   DESIGNER:   Sanders Lee
*
*   PROGRAMMER: Sanders Lee
*
*   INTERFACE: playHurtSound()
*
*   PARAMETERS: void
*
*   RETURNS: void
*
*   NOTES: Plays hurt sound associated with this enemy
******************************************************************************/
void MiniBoss::playHurtSound()
{
    sf::Vector2f soundPos(left + newXSpeed, top + newYSpeed);
	voice.setPosition(left + newXSpeed, top + newYSpeed, 0);  // this line prevent's enemy's
															  // voice from fading & being off-center
	voice.setMinDistance(3.0);
	voice = SoundManager::play(hurtSoundMBoss, soundPos);
	voice.play();
}

/******************************************************************************
*   FUNCTION: playAttackSound()
*
*   DATE: April 6 2014
*
*   REVISIONS: Filip Gutica    - Moved from on update to seperate function
*
*   DESIGNER:   Sanders Lee
*
*   PROGRAMMER: Sanders Lee
*
*   INTERFACE: playAttackSound()
*
*   PARAMETERS: void
*
*   RETURNS: void
*
*   NOTES: Plays attack sound associated with this enemy
******************************************************************************/
void MiniBoss::playAttackSound()
{
    sf::Vector2f soundPos(left + newXSpeed, top + newYSpeed);
	voice.setPosition(left + newXSpeed, top + newYSpeed, 0);  // this line prevent's enemy's
															  // voice from fading & being off-center
	voice.setMinDistance(3.0);
	voice = SoundManager::play(attackSoundMBoss, soundPos);
	voice.play();
}

/******************************************************************************
*   FUNCTION: animate()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: animate()
*
*   PARAMETERS: void
*
*   RETURNS: void
*
*   NOTES: Performs the apprpriate animation for this enemy.
******************************************************************************/
void MiniBoss::animate()
{
  if (isMoving())
    gkAnimation->step(1);
}

/******************************************************************************
*   FUNCTION: isMoving()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: isMoving()
*
*   PARAMETERS: void
*
*   RETURNS: bool   - If this enemy is moving
*
*   NOTES: Returns true if enemy is moving, false otherwise
******************************************************************************/
bool MiniBoss::isMoving()
{
  return (movingLeft || movingRight || movingUp || movingDown);
}

/******************************************************************************
*   FUNCTION: setRange(int)
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: setRange(int)
*
*   PARAMETERS: r   - New range for this enemy
*
*   RETURNS: void
*
*   NOTES: Sets a new range for this enemy
******************************************************************************/
void MiniBoss::setRange(int r)
{
  _range = r;
}

/******************************************************************************
*   FUNCTION: setHealth
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: setHealth(int h)
*
*   PARAMETERS: h   - new Health for this enemy
*
*   RETURNS: void
*
*   NOTES: Sets a new health for this enemy
******************************************************************************/
void MiniBoss::setHealth(int h)
{
  _health = h;
}

/******************************************************************************
*   FUNCTION: setAttack
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: setAttack(int a)
*
*   PARAMETERS: a   - new attack for enemy
*
*   RETURNS: void
*
*   NOTES: Sets new attack for the enemy
******************************************************************************/
void MiniBoss::setAttack(int a)
{
  _attack = a;
}

/******************************************************************************
*   FUNCTION: setAttackSpeed()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: setAttackSpeed(float as)
*
*   PARAMETERS: as    - New attack speed for the enemy
*
*   RETURNS: void
*
*   NOTES: Sets new attack speed for the enemy
******************************************************************************/
void MiniBoss::setAttackSpeed(float as)
{
  _attackSpeed == as;
}

/******************************************************************************
*   FUNCTION: setXSpeed
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: setXSpeed(float x)
*
*   PARAMETERS: x   - new horizonatl speed for this enemy
*
*   RETURNS: void
*
*   NOTES: Sets new horizontal speed for this enemy
******************************************************************************/
void MiniBoss::setXSpeed(float x)
{
  _xSpeed = x;
}

/******************************************************************************
*   FUNCTION: setYSpeed
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: setYSpeed(float y)
*
*   PARAMETERS: y   - new Vertical speeed for the enemy
*
*   RETURNS: void
*
*   NOTES: Set new vertical speed for the enemy
******************************************************************************/
void MiniBoss::setYSpeed(float y)
{
  _ySpeed = y;
}

/******************************************************************************
*   FUNCTION: setSpeed
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: setSpeed(int speed)
*
*   PARAMETERS: speed   new horizontal and vertical speed for enemy
*
*   RETURNS:  void
*
*   NOTES: set new horizontal and vertical speed for the enemy
******************************************************************************/
void MiniBoss::setSpeed(int _speed)
{
    _xSpeed = _speed;
    _ySpeed = _speed;
}

/******************************************************************************
*   FUNCTION: getXSpeed()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: getXSpeed()
*
*   PARAMETERS: void
*
*   RETURNS: float   - x speed
*
*   NOTES: Returns the average of the x and y speeds for this enemy
******************************************************************************/
float MiniBoss::getXSpeed()
{
	return _xSpeed;
}

/******************************************************************************
*   FUNCTION: getYSpeed()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: getYSpeed()
*
*   PARAMETERS: void
*
*   RETURNS: float   - y speed
*
*   NOTES: Returns the average of the x and y speeds for this enemy
******************************************************************************/
float MiniBoss::getYSpeed()
{
	return _ySpeed;
}

/******************************************************************************
*   FUNCTION: getSpeed()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: getSpeed()
*
*   PARAMETERS: void
*
*   RETURNS: int   - Avarage speed of the enemy
*
*   NOTES: Returns the average of the x and y speeds for this enemy
******************************************************************************/
int MiniBoss::getSpeed()
{
	return _xSpeed;
}

/******************************************************************************
*   FUNCTION: getRange()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: getRange()
*
*   PARAMETERS: void
*
*   RETURNS: int   - Range (attack and aggro) of this enemy
*
*   NOTES: Returns the range of this enemy
******************************************************************************/
int MiniBoss::getRange()
{
  return _range;
}

/******************************************************************************
*   FUNCTION: getHealth()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: getHealth()
*
*   PARAMETERS: void
*
*   RETURNS: int   - current health of the enemy
*
*   NOTES: Returns current health of the enemy
******************************************************************************/
int MiniBoss::getHealth()
{
  return _health;
}

/******************************************************************************
*   FUNCTION: getAttack()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: getAttack()
*
*   PARAMETERS: void
*
*   RETURNS: int   - Attack of this enemy
*
*   NOTES: Returns attack of the enemy (attack power)
******************************************************************************/
int MiniBoss::getAttack()
{
  return _attack;
}

/******************************************************************************
*   FUNCTION: getAttackSpeed()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: getAttackSpeed()
*
*   PARAMETERS: void
*
*   RETURNS: float   - Attack speed of this enemy
*
*   NOTES: returns enemy's attack speed
******************************************************************************/
float MiniBoss::getAttackSpeed()
{
  return _attackSpeed;
}


/******************************************************************************
*   FUNCTION: turn()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: turn()
*
*   PARAMETERS: void
*
*   RETURNS:
*
*   NOTES:
******************************************************************************/
void MiniBoss::turn()
{

}

/******************************************************************************
*   FUNCTION: onCreate()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: onCreate()
*
*   PARAMETERS: void
*
*   RETURNS:
*
*   NOTES:
******************************************************************************/
void MiniBoss::onCreate()
{

}

/******************************************************************************
*   FUNCTION: stopAllSounds()
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: stopAllSounds()
*
*   PARAMETERS: void
*
*   RETURNS: void
*
*   NOTES: Stops gatekeeper sounds
******************************************************************************/
void MiniBoss::stopAllSounds()
{
    footstep.stop();
}

/******************************************************************************
*   FUNCTION: operator==
*
*   DATE: April 6 2014
*
*   DESIGNER:   Filip Gutica
*
*   PROGRAMMER: Filip Gutica
*
*   INTERFACE: operator==(const VEntity&)
*
*   PARAMETERS: void
*
*   RETURNS: bool   - true
*
*   NOTES: Overloaded compare operator
******************************************************************************/
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
