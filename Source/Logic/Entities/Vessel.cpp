#include <iostream>
#include "Vessel.h"
#include "../Event.h"

//TO DO:
//1) GIVE IT A SPRITE
//2) MAKE THE SPRITE ANIMATE
//3) DIAGONAL MODEMENT

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Vessel constructor
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sebastian Pelka, Sanders Lee
--
-- PROGRAMMER: Sebastian Pelka, Sanders Lee
--
-- INTERFACE: Vessel::Vessel( job_class jobclass, GameMap gmap, int x, int y )
-- job_class jobclass: the job class you wish to set up the Vessel as
-- GameMap gmap: the game map the Vessel is on
-- int x, int y: the coordinates of the Vessel on the map
--
-- RETURNS: nothing
--
-- NOTES:
-- This function is used to generate a Vessel and set up its position on the game map
----------------------------------------------------------------------------------------------------------------------*/
Vessel::Vessel( SGO &_sprite, SGO &_mask, SGO &_weapon,
	Marx::Map * gmap,
	float x,
	float y,
	Marx::Controller* controller_,
	float height,
	float width
	/*, job_class jobClass, Ability* abilityList*/ )
			: Marx::VEntity(_sprite, gmap, x, y, controller_, 1.0, 1.0 ),
			mask_sprite(_mask),
			weapon_sprite(_weapon)
			/*atk_sprite(_mask),
			satk_sprite(_mask)*/
			//,_controller(controller)
{

	direction = 1; //start facing right

	atk_sprite = *(new SGO());
	satk_sprite = *(new SGO());

	resetEXP();
	xSpeed = 0.1;
	ySpeed = 0.1;
	movingLeft = false;
    movingRight = false;
    movingUp = false;
    movingDown = false;
	attackPower = 0;
	xPos = x;
	yPos = y;

	//abilities = abilityList;
/*
	//class-specific instantiation
	if ( jobClass == WARRIOR )			//warrior
	{
		currentHealth = 150;
		maxHealth = 150;
		travelSpeed = 2;
		//Weapon = Spear;
	}
	else if ( jobClass == SHAMAN )		//shaman
	{
		currentHealth = 75;
		maxHealth = 75;
		travelSpeed = 6;
		//weapon = Fireball;
	}
	else if ( jobClass == HUNTER )		//Hunter
	{
		currentHealth = 100;
		maxHealth = 100;
		travelSpeed = 6;
		//weapon = Javelin;
	}
	else if ( jobClass == SCOUT ) 		//Scout
	{
		currentHealth = 125;
		maxHealth = 125;
		travelSpeed = 7;
		//weapon = Sword;
	}
	else if (jobClass == TEGUH) 		//TEGUH
	{
		currentHealth = 4242;
		maxHealth = 424242;
		travelSpeed = 42;
		//weapon = BOWL_OF_LAKSA;
	}*/
	this->add(mask_sprite);
	this->add(weapon_sprite);

	std::cout << "Vessel constructed successfully!" << std::endl;
}

/*-------------------------------------------
--
--
-- Called every game loop. dequeus all events from the entity's
-- controller and proceses those events
---------------------------------------------*/
void Vessel::onUpdate()
{

	static float newXSpeed = 0;
	static float newYSpeed = 0;

	std::vector<Marx::Event*>* eventQueue = getController()->getEvents();
	for( std::vector< Marx::Event*>::iterator it = eventQueue->begin()
		; it != eventQueue->end()
		; ++it )
	{
		std::cout << (*it)->type << std::endl;
		// switch on type
		switch((*it)->type)
		{
			case ::Marx::MOVE:
			{
				MoveEvent* ev = (MoveEvent*) (*it);
                int xDir = ev->getXDir();
                int yDir = ev->getYDir();

								if (yDir == -1)
								{
									newYSpeed -= ySpeed;
									std::cout << "Vessel.cpp: moving up" << std::endl;
								}
								else if (yDir == 1)
								{
									newYSpeed += ySpeed;
									std::cout << "Vessel.cpp: moving down" << std::endl;
								}
								else if (xDir == 1)
								{
									newXSpeed += xSpeed;
									std::cout << "Vessel.cpp: moving right" << std::endl;
								}
								else if (xDir == -1)
								{
									newXSpeed -= xSpeed;
									std::cout << "Vessel.cpp: moving left" << std::endl;
								}

								//old code - replaced with the if-else block above
                //movingLeft = (xDir < 0);
                //movingRight = (xDir > 0);
                //movingUp = (yDir < 0);
                //movingDown = (yDir > 0);
				break;
			}
			case ::Marx::ATTACK:
			{
				AttackEvent* aev = (AttackEvent*) (*it);
				std::cout << "ATTACK" << std::endl;
				createAttack(*aev, atk_sprite, left, top);
			}
			case ::Marx::SK_ATTACK:
			{

				SkillAttackEvent* saev = (SkillAttackEvent*) (*it);
				std::cout << "ATTACK" << std::endl;
				createSkAttack(*saev, satk_sprite, left, top);
			}
            case ::Marx::SET_HEALTH:
            {
                SetHealthEvent* ev = (SetHealthEvent*) (*it);
                
                setHealth(ev->getChange());
            }
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

/*---------
-- Calls the function to draw the body around, and handles the movement of the
-- mask and weapon in Vessel.cpp
--
--------------*/
/*
void Vessel::draw(Renderer& renderer, sf::RenderStates states) const
{
	std::cout << "vessel's draw called" << std::endl;
	VEntity::draw(renderer, states);
	sf::FloatRect* tile = Manager::TileManager::get(map->getCell(0, 0)->getTileId());
	states.transform.translate(left * tile->width, (top + height) * tile->height);

	renderer.draw(mask_sprite, states);
	renderer.draw(weapon_sprite, states);

}
*/

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Vessel destructor
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: Vessel::~Vessel( )
--
-- RETURNS: nothing
--
-- NOTES:
-- This function is used to destroy a vessel object and free its members from memory.
----------------------------------------------------------------------------------------------------------------------*/
Vessel::~Vessel()
{
	if( abilities != NULL )
		delete[] abilities;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: resetEXP
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Vessel::resetEXP()
--
-- RETURNS: nothing
--
-- NOTES:
-- Resets a Vessel's EXP so it's 0 and the Vessel is at level 1.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::resetEXP()
{
	currentEXP = 0;
	nextLevelEXP = 100;
	currentLevel = 1;

	//class-specific instantiation
	if ( jobClass == WARRIOR )			//warrior
	{
		currentHealth = 150;
		maxHealth = 150;
		defaultSpeed = travelSpeed = 2;
		//Weapon = Spear;
	}
	else if ( jobClass == SHAMAN )		//shaman
	{
		currentHealth = 75;
		maxHealth = 75;
		defaultSpeed = travelSpeed = 6;
		//weapon = Fireball;
	}

	else if ( jobClass == HUNTER )		//Hunter
	{
		currentHealth = 100;
		maxHealth = 100;
		defaultSpeed = travelSpeed = 6;
		//weapon = Javelin;
	}
	else if ( jobClass == SCOUT ) 		//Scout
	{
		currentHealth = 125;
		maxHealth = 125;
		defaultSpeed = travelSpeed = 7;
		//weapon = Sword;
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: increaseEXP
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Vessel::increaseEXP( int exp )
-- int exp: the amount of exp increase by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function adds the given EXP to current EXP count.
-- If current EXP >= total next level EXP, increase level by one,
-- increase total next level EXP by a multiplication factor,
-- increase max health by a a multiplication factor,
-- increase speed by 1;
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::increaseEXP( int exp )
{
	currentEXP += exp;

	if( currentLevel < 10 )
	{
		if( currentEXP >= nextLevelEXP )
		{
			currentLevel++;
			if( currentLevel == 10 )
				nextLevelEXP *= 2.5;
			maxHealth *= 1.5;
			defaultSpeed++;
			travelSpeed++;
		}
	}
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getEXP
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: int Vessel::getEXP()
--
-- RETURNS: EXP in integer format
--
-- NOTES:
-- This function gets the current amount of EXP the Vessel has.
----------------------------------------------------------------------------------------------------------------------*/
int Vessel::getEXP()
{
	return currentEXP;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getNextLevelEXP
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: int Vessel::getNextLevelEXP()
--
-- RETURNS: EXP in integer format
--
-- NOTES:
-- This function returns the next TOTAL experience points needed to level up.
----------------------------------------------------------------------------------------------------------------------*/
int Vessel::getNextLevelEXP()
{
	return nextLevelEXP;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getLevel
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: int Vessel::getLevel()
--
-- RETURNS: the Vessel's level as an integer
--
-- NOTES:
-- This function returns the Vessel's current level.
----------------------------------------------------------------------------------------------------------------------*/
int Vessel::getLevel()
{
	return currentLevel;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: increaseLevel
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE: void Vessel::increaseLevel()
--
-- RETURNS: void
--
-- NOTES:
-- This function increments the Vessel's current level.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::increaseLevel()
{
		currentLevel++;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: resetHP
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Vessel::resetHP()
--
-- RETURNS: nothing
--
-- NOTES:
-- This function resets the Vessel's HP to the current level's maximum HP
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::resetHP()
{
	currentHealth = maxHealth;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: increaseHP
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Vessel::increaseHP( int hp )
-- int hp: the amount of HP to increase by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function increases the Vessel's HP, but not above the current level's maximum HP. Used as a healing function.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::increaseHP( int hp )
{
	currentHealth += hp;
	if( currentHealth > maxHealth )
		currentHealth = maxHealth;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: decreaseHP
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Vessel::decreaseHP( int hp )
-- int hp: the amount of HP to decrease by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function decrease the Vessel's HP, but not below 0. Used as a take-damage function.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::decreaseHP( int hp )
{
	currentHealth -= hp;
	if( currentHealth < 0 )
	{
		currentHealth = 0;
		die();
	}
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getMaxHP
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: int Vessel::getMaxHP()
--
-- RETURNS: Max HP as an integer
--
-- NOTES:
-- This function returns the maximum HP the Vessel can have at the current level
----------------------------------------------------------------------------------------------------------------------*/
int Vessel::getMaxHP()
{
	return maxHealth;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: resetAttackPower
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Vessel::resetAttackPower()
--
-- RETURNS: nothing
--
-- NOTES:
-- This function resets the Vessel's attack power to what's normal for the current level
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::resetAttackPower()
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: attackPowerUp
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Vessel::attackPowerUp( int attackpower )
-- int attackpower: the amount of attack power to increase by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function increases the Vessel's attack power. Used as a power up function.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::attackPowerUp( int attackpower )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: attackPowerDown
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Vessel::attackPowerDown( int attackpower )
-- int attackpower: the amount of attack power to decrease by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function decreases the Vessel's attack power, but not below 0.. Used as a power down function.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::attackPowerDown( int attackpower )
{
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getAttackPower
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: int Vessel::getAttackPower()
--
-- RETURNS: Attack power as an integer
--
-- NOTES:
-- This function returns the Vessel's current attack power.
----------------------------------------------------------------------------------------------------------------------*/
int Vessel::getAttackPower()
{
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getDefaultAttackPower
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: int Vessel::getDefaultAttackPower()
--
-- RETURNS: default attack power for the level as an integer
--
-- NOTES:
-- This function returns the default attack power for the current level
----------------------------------------------------------------------------------------------------------------------*/
int Vessel::getDefaultAttackPower()
{
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: resetSpeed
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Vessel::resetSpeed()
--
-- RETURNS: nothing
--
-- NOTES:
-- This function resets the Vessel's speed to what's normal for the current level.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::resetSpeed()
{
		travelSpeed = defaultSpeed;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: speedUp
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Vessel::speedUp( int speed )
-- int speed: the amount of speed to increase by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function increases the Vessel's speed. Used as a power up function.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::speedUp( int speed )
{
	travelSpeed++;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: speedDown
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Vessel::speedDown( int speed )
-- int speed: the amount of speed to decrease by
--
-- RETURNS: nothing
--
-- NOTES:
-- This function decreases the Vessel's speed, but not below 0. Used as a power down function.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::speedDown( int speed )
{
	if( travelSpeed > 1 )
		speed--;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getSpeed
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: int Vessel::getSpeed()
--
-- RETURNS: current speed as an integer
--
-- NOTES:
-- This function returns the current speed the Vessel has
----------------------------------------------------------------------------------------------------------------------*/
int Vessel::getSpeed()
{
    return travelSpeed;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getDefaultSpeed
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: int Vessel::getDefaultSpeed()
--
-- RETURNS: default speed for the level as an integer
--
-- NOTES:
-- This function returns the default speed for the current level
----------------------------------------------------------------------------------------------------------------------*/
int Vessel::getDefaultSpeed()
{
	return defaultSpeed;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: checkDeath
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: bool Vessel::checkDeath()
--
-- RETURNS: whether the Vessel is dead as a boolean value
--
-- NOTES:
-- This function checks to see if the Vessel's HP has reached 0. If true, return 0 and maybe call death animation.
----------------------------------------------------------------------------------------------------------------------*/
bool Vessel::checkDeath()
{
	return false;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: die
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE: void Vessel::die()
--
-- RETURNS: void
--
-- NOTES:
-- Invokes a death animation, destructor, and any other housekeeping functions that need to occur when a Vessel dies.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::die()
{

}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: normalAttack
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE: void Vessel::normalAttack( int x, int y )
-- int x, int y: the target position of the attack
--
-- RETURNS: nothing
--
-- NOTES:
-- This function attempts to launch a normal attack at the target coordinate. Depending on normal weapon type, the
-- attack may fail because the target is out of range.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::normalAttack( int x, int y )
{
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: useAbility
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE: void useAbility( int abilityNum, int x, int y )
-- abilityNum: the position of the ability in the Vessel's ability array
-- int x, int y: the target position of the attack
--
-- RETURNS: nothing
--
-- NOTES:
-- This function attempts use an ability on the designated X, Y coordinates.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::useAbility( int abilityNum, int x, int y )		//possibly need an Entity parameter for abilities that target an entity, such as healing
{
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getXSpeed
--
-- DATE: February 27, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Vessel::getXSpeed()
--
-- RETURNS: x velocity as integer
--
-- NOTES:
-- Returns the x velocity of the vessel.
----------------------------------------------------------------------------------------------------------------------*/
int Vessel::getXSpeed()
{
	return xSpeed;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getYSpeed
--
-- DATE: February 27, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Vessel::getYSpeed()
--
-- RETURNS: y velocity as integer
--
-- NOTES:
-- Returns the y velocity of the vessel.
----------------------------------------------------------------------------------------------------------------------*/
int Vessel::getYSpeed()
{
	return ySpeed;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: isMoving
--
-- DATE: February 27, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: bool Vessel::isMoving()
--
-- RETURNS: moving state as boolean
--
-- NOTES:
-- Returns whether the vessel is moving or not as a boolean.
----------------------------------------------------------------------------------------------------------------------*/
bool Vessel::isMoving()
{
	return (movingLeft || movingRight || movingUp || movingDown);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getDirection
--
-- DATE: February 27, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: int Vessel::getDirection()
--
-- RETURNS: current direction as integer
--
-- NOTES:
-- Returns the direction the vessel is facing.
-- 0 = left, 1 = right
----------------------------------------------------------------------------------------------------------------------*/
int Vessel::getDirection()
{
	return direction;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getJobClass
--
-- DATE: February 27, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- INTERFACE: job_class Vessel::getJobClass()
--
-- RETURNS: job class as enum value
--
-- NOTES:
-- Returns the job class of the vessel.
----------------------------------------------------------------------------------------------------------------------*/
job_class Vessel::getJobClass()
{
	return jobClass;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setHealth
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Calvin Rempel
--
-- PROGRAMMER:	Calvin Rempel
--
-- INTERFACE: void setHealth(int health)
-- int attack: the amount to set health to
--
-- RETURNS: nothing
--
-- NOTES:
-- This function provides a common interface for setting health for
-- all Creatures.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::setHealth(int health)
{
    currentHealth = health;

    if (currentHealth < 0)
        currentHealth = 0;
    else if (currentHealth > maxHealth)
        currentHealth = maxHealth;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getHealth
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Calvin Rempel
--
-- PROGRAMMER:	Calvin Rempel
--
-- INTERFACE: int Vessel::getHealth()
--
-- RETURNS: int - The current health of the vessel.
--
-- NOTES:
-- This function returns the current health of the vessel.
----------------------------------------------------------------------------------------------------------------------*/
int Vessel::getHealth()
{
    return currentHealth;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setAttack
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Calvin Rempel
--
-- PROGRAMMER:	Calvin Rempel
--
-- INTERFACE: void setAttack(int attack)
-- int attack: the amount to set attack power to
--
-- RETURNS: nothing
--
-- NOTES:
-- This function provides a common interface for increasing attack power for
-- all Creatures.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::setAttack(int attack)
{
    attackPower = attack;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: setAttack
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
Entity *Vessel::getEntity()
{
    return this;
}

float Vessel::getYPosition()
{
	return xPos;
}

float Vessel::getXPosition()
{
	return yPos;
}
