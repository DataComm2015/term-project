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
**              Chris Klassen
**              Lewis Scott
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

const char *MiniBee::travelSnds[4] = {"Assets/Sound/Enemies/bee/babby/bee_travel_01_baby.ogg",
                                        "Assets/Sound/Enemies/bee/babby/bee_travel_02_baby.ogg",
                                        "Assets/Sound/Enemies/bee/babby/bee_travel_angry_01_baby.ogg",
                                        "Assets/Sound/Enemies/bee/babby/bee_travel_angry_02_baby.ogg"};

const char *MiniBee::attackSnds[3] = {"Assets/Sound/Enemies/bee/babby/bee_attack_01_baby.ogg",
                                        "Assets/Sound/Enemies/bee/babby/bee_attack_02_baby.ogg",
                                        "Assets/Sound/Enemies/bee/babby/bee_attack_03_baby.ogg"};

const char *MiniBee::hurtSnds[4] = {"Assets/Sound/Enemies/bee/babby/bee_hurt_01_baby.ogg",
                                      "Assets/Sound/Enemies/bee/babby/bee_hurt_02_baby.ogg",
                                      "Assets/Sound/Enemies/bee/babby/bee_hurt_03_baby.ogg",
                                      "Assets/Sound/Enemies/bee/babby/bee_hurt_04_baby.ogg"};

const char *MiniBee::deathSnds[3] = {"Assets/Sound/Enemies/bee/babby/bee_death_01_baby.ogg",
                                        "Assets/Sound/Enemies/bee/babby/bee_death_02_baby.ogg",
                                        "Assets/Sound/Enemies/bee/babby/bee_death_03_baby.ogg"};

id_resource beeShadow;


/******************************************************************************
*   FUNCTION: MiniBee() Constructor
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
*   NOTES: Constructor for mini bees. Initializes the gate keeper sets attributes
*          Sets animation.
******************************************************************************/

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

    grassWalkSoundMiniBee = SoundManager::store(SoundManager::load(MiniBee::travelSnds[rand() % 4]));
    stoneWalkSoundMiniBee = SoundManager::store(SoundManager::load(MiniBee::travelSnds[rand() % 4]));
    hurtSoundMiniBee   = SoundManager::store(SoundManager::load(MiniBee::hurtSnds[rand() % 4]));
    attackSoundMiniBee   = SoundManager::store(SoundManager::load(MiniBee::attackSnds[rand() % 3]));

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
void MiniBee::processSkillEvent(SkillEvent* ev)
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
void MiniBee::processSetHealthEvent(SetHealthEvent* ev)
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
void MiniBee::processAttackEvent(AttackEvent* aev)
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
void MiniBee::playHurtSound()
{
    sf::Vector2f soundPos(left + newXSpeed, top + newYSpeed);
	voice.setPosition(left + newXSpeed, top + newYSpeed, 0);  // this line prevent's enemy's
															  // voice from fading & being off-center
	voice.setMinDistance(3.0);
	voice = SoundManager::play(hurtSoundMiniBee, soundPos);
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
void MiniBee::playAttackSound()
{
    sf::Vector2f soundPos(left + newXSpeed, top + newYSpeed);
	voice.setPosition(left + newXSpeed, top + newYSpeed, 0);  // this line prevent's enemy's
															  // voice from fading & being off-center
	voice.setMinDistance(3.0);
	voice = SoundManager::play(attackSoundMiniBee, soundPos);
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
void MiniBee::animate()
{
  if (isMoving())
    gkAnimation->step(1);
  else
    gkAnimation->step(5);
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
bool MiniBee::isMoving()
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
void MiniBee::setRange(int r)
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
void MiniBee::setHealth(int h)
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
void MiniBee::setAttack(int a)
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
void MiniBee::setAttackSpeed(float as)
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
void MiniBee::setXSpeed(float x)
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
void MiniBee::setYSpeed(float y)
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
void MiniBee::setSpeed(int _speed)
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
float MiniBee::getXSpeed()
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
float MiniBee::getYSpeed()
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
int MiniBee::getSpeed()
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
int MiniBee::getRange()
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
int MiniBee::getHealth()
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
int MiniBee::getAttack()
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
float MiniBee::getAttackSpeed()
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
void MiniBee::turn()
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
void MiniBee::onCreate()
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
void MiniBee::stopAllSounds()
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
