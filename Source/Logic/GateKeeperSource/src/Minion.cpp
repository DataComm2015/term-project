/********************************************************************************
**	SOURCE FILE:	Minion.cpp -
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
#include "Minion.h"
#include "../../Event.h"
#include "../../Entities/ServerEnemyController.h"
#include <typeinfo>
#include <iostream>
#include <cstdlib>

using namespace Manager;

// sound set loaded should be determined by enemy type
//static id_resource grassWalkSoundMinion = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_travel_01.ogg"));
//static id_resource stoneWalkSoundMinion = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_travel_01.ogg"));
//static id_resource hurtSoundMinion 			= SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_hurt_01.ogg"));
//static id_resource attackSoundMinion		= SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_attack_01.ogg"));

// bug fix by Sanders Lee
Minion::Minion(SGO& sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0) :
GateKeeper(sprite, map, x, y, ctrl, h, w)
{
    _range = 10;
    _health = 100;
    _type = 1;
    _attack = 1;
    _attackSpeed = 3;
    _xPos = x;
    _yPos = y;
    _xSpeed = 0.03;
    _ySpeed = 0.03;
    movingLeft = movingRight = movingUp = movingDown = _moving = false;


    int randDirection = (rand() % 3) - 1;

    getSprite().sprite().setScale(randDirection, 1);

    gkAnimation = new Animation(&sprite, sf::Vector2i(32, 32), 8, 7);

}

Minion::~Minion()
{
    footstep.stop();
}

/***
-- PROGRAMMER:  Filip Gutica
--				Sanders Lee (Debugged synchronization problem across clients,
--                           Added sound for GateKeeper travel)
***/
void Minion::onUpdate(float deltaTime)
{
  //Perform the generic gatekeeper animation
  animate();

  //  std::cout << "GateKeeper.cpp ON UPDATE." << std::endl;
  std::vector<Marx::Event*>* eventQueue = getController()->getEvents();
  for( std::vector< Marx::Event*>::iterator it = eventQueue->begin()
      ; it != eventQueue->end()
      ; ++it )
  {
        int xDir;
        int yDir;
        MoveEvent* ev;
    // switch on type
    switch((*it)->type)
    {
    	case ::Marx::MOVE:
		{
    		ev = (MoveEvent*) (*it);
			xDir = ev->getXDir();
			yDir = ev->getYDir();

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
		case ::Marx::SET_HEALTH:
		{
			SetHealthEvent * event = (SetHealthEvent*)(*it);
			_health = getHealth()-event->getChange();
			
			Controller * cont = dynamic_cast<Controller*>(NetworkEntityMultiplexer::getInstance()->getEntityById(event->getEntId()));
			AddPointsEvent *pointsEvent = new AddPointsEvent(event->getChange());
			cont->addEvent(pointsEvent);

			if(_health <= 0)
			{
				std::cout << "Minion Dead" << std::endl;
				onDestroy();
			}

            break;
		}
		case ::Marx::ATTACK:
		{
			_attackSpeed -= deltaTime;
			if (_attackSpeed <= 0)
			{
				SkillAttackEvent* saev = (SkillAttackEvent*) (*it);
				std::cout << "ATTACK" << std::endl;
				createSkAttack(*saev, getSprite(), left, top);
				_attackSpeed = 3;
			}
			break;
		}
        case ::Marx::SKILL:
        {
            // process the skill event, and increase/decrease hp and stuff
            SkillEvent *ev = (SkillEvent*)(*it);
            printf("GateKeeper BEFORE Health: %d\n", _health);
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
            
            printf("GateKeeper AFTER Health: %d\n", _health);
            
            if(_health <= 0)
            {
              std::cout << "Moving GateKeeper to ambiguous destination!!" << std::endl;
              onDestroy();
            }
            break;
        }
    }


  }
  getController()->clearEvents();




  Entity::rMove(newXSpeed, newYSpeed,false);


}

void Minion::playSound(float xSpeed, float ySpeed)
{
/*  soundActive = false;
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
      footstep = SoundManager::play(grassWalkSoundMinion, soundPos);
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
      footstep = SoundManager::play(stoneWalkSoundMinion, soundPos);
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

void Minion::animate()
{
  if (isMoving())
    gkAnimation->step(1);
  else
    gkAnimation->step(5);
}

bool Minion::isMoving()
{
  return (movingLeft || movingRight || movingUp || movingDown);
}

void Minion::setRange(int r)
{
  _range = r;
}

void Minion::setHealth(int h)
{
  _health = h;
}

void Minion::setAttack(int a)
{
  _attack = a;
}

void Minion::setAttackSpeed(float as)
{
  _attackSpeed == as;
}


void Minion::setXSpeed(float x)
{
  _xSpeed = x;
}

void Minion::setYSpeed(float y)
{
  _ySpeed = y;
}

void Minion::setSpeed(int _speed)
{
    _xSpeed = _speed;
    _ySpeed = _speed;
}

int Minion::getSpeed()
{
	return _xSpeed;
}

int Minion::getRange()
{
  return _range;
}

int Minion::getHealth()
{
  return _health;
}

int Minion::getAttack()
{
  return _attack;
}

float Minion::getAttackSpeed()
{
  return _attackSpeed;
}

int Minion::getMovementSpeed()
{
  return _movementSpeed;
}

void Minion::turn()
{

}

void Minion::onCreate()
{

}

void Minion::stopAllSounds()
{
    footstep.stop();
}

bool Minion::operator==(const VEntity&)
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
Entity *Minion::getEntity()
{
    return this;
}
