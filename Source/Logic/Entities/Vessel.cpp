/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Vessel.cpp
--
-- PROGRAM: Sojourn
--
-- FUNCTIONS:
--		Vessel::Vessel( SGO& _sprite, SGO _mask, SGO _weapon, Marx::Map * gmap, float x, float y, Marx::Controller* controller_,
--			float height, float width)
--		~Vessel();
--		void Vessel::onUpdate(float deltaTime)
--		void Vessel::setPlayerEntity(PlayerEntity *entity)
--		void Vessel::playFootstepSound()
--		void Vessel::playHurtSound()
--		void Vessel::playAttackSound()
--
--
-- DATE: February 15, 2015
--
-- REVISIONS: N/A
--
-- DESIGNER: Sebastian Pelka
--
-- PROGRAMMER:  Sebastian Pelka
--
-- NOTES:
--        This file contains the Vessel class implementation.
----------------------------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <time.h>
#include <cmath>
#include "Vessel.h"
#include "../Event.h"
#include "../Skills.h"
#include "../../Multimedia/manager/SoundManager.h"
#include "../../Engine/AttackAction.h"
#include "PlayerEntity.h"

#define ATTACK_COOLDOWN 0.5F

using namespace Manager;

Animation *runAnim;
Animation *runAnim_mask;
Animation *runAnim_wep;
sf::Clock vesselClock;

id_resource Vessel::grassWalkSound = SoundManager::store(SoundManager::load("Assets/Sound/Player/Run/run_grass.ogg"));
id_resource Vessel::stoneWalkSound = SoundManager::store(SoundManager::load("Assets/Sound/Player/Run/run_stone.ogg"));
id_resource Vessel::hurtSound = SoundManager::store(SoundManager::load("Assets/Sound/Player/Hurt/vessel_hurt.ogg"));
id_resource Vessel::attackSound = SoundManager::store(SoundManager::load("Assets/Sound/Player/Attack/whip_01.ogg"));
id_resource vesselShadow;

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Vessel constructor
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--		Sebastian Pelka and Melvin Loho March 31, 2015
--				Solved Rendering Issues
--		Sebastian Pelka		April 1, 2015
--				updated the constructor for animations
--
-- DESIGNER: Sebastian Pelka, Sanders Lee
-- PROGRAMMER: Sebastian Pelka, Sanders Lee, Jeff Bayntun, Chris Klassen
--
-- INTERFACE: Vessel::Vessel( job_class jobclass, GameMap gmap, int x, int y )
-- 		job_class jobclass: the job class you wish to set up the Vessel as
-- 		GameMap gmap: the game map the Vessel is on
-- 		int x, int y: the coordinates of the Vessel on the map
--		controller_ a pointer to the controller for this class
--		height, width: the height and width of the object
--
-- RETURNS: nothing
--
-- NOTES:
-- This function is used to generate a Vessel and set up its position on the game map
----------------------------------------------------------------------------------------------------------------------*/
Vessel::Vessel( SGO& _sprite, SGO _mask, SGO _weapon,
		Marx::Map * gmap,
		float x,
		float y,
		Marx::Controller* controller_,
		float height,
		float width
		)
		: Marx::VEntity(_sprite, gmap, x, y, controller_, 1.0, 1.0, ENTITY_TYPES::VESSEL),
		mask_sprite(_mask),
		weapon_sprite(_weapon)
{
	attCool = 2;
	direction = 1; //start facing right

	xSpeed = 0.08;
	ySpeed = 0.08;
	movingLeft = false;
	movingRight = false;
	movingUp = false;
	movingDown = false;
	attackPower = 0;
    newXSpeed = 0;
    newYSpeed = 0;

	xPos = x;
	yPos = y;

    newYSpeed = 0;
    newXSpeed = 0;

	servX = 0;
	servY = 0;

	myX = 0;
	myY = 0;

	currentHealth = 100;
	maxHealth = 100;

	runAnim = new Animation(&_sprite, sf::Vector2i(32, 32), 8, 3);
	runAnim_mask = new Animation(&mask_sprite, sf::Vector2i(32, 32), 8, 3);
	runAnim_wep = new Animation(&weapon_sprite, sf::Vector2i(32, 32), 8, 3);

	this->add(mask_sprite);
  	this->add(weapon_sprite);

	// Add the drop shadow
	vesselShadow = Manager::TextureManager::store(
			Manager::TextureManager::load("Assets/Art/Shadows/vessel_shadow.png")
	);

	shadow.sprite().setTexture(*Manager::TextureManager::get(vesselShadow));
	shadow.sprite().setTextureRect(sf::IntRect(0, 0, 15, 6));

	this->add(shadow);
	shadow.sprite().setOrigin(-6, -28);

	myHealthBar = NULL;

	std::cout << "Vessel constructed successfully!" << std::endl;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        Vessel::onUpdate(float deltaTime)
--
-- DATE:            March 27, 2015
--
-- REVISIONS:       (Date and Description)
-- 		Sebastian Pelka	and Thomas Tallentire March 27, 2015
--				Updated the function to extend VEntity and use its move function
--		Sebastian Pelka and Eric Tsang March 28, 2015
--				Integrated the vessel to move by sending signals to the network
--		Sebastian Pelka March 29, 2015
--				Simplified movement to use vectors
--		Sebastian Pelka April 1, 2015
--				Vessel body animation implemented
--		Sebastian Pelka April 3, 2015
--				Mask and spear animation implemented
--		Sebastian Pelka and Sanders Lee April 6, 2015
--				Hooked the Animations into the new testbed. Animations are done.
--		Sanders Lee
--				Debugged synchronization problem across clients, Added sound for walking
--
-- DESIGNER:        Sebastian Pelka
--
-- PROGRAMMER:      Sebastian Pelka, Sanders Lee, Alex Lam, Julian Brandrick, Thomas Tallentire
--
-- INTERFACE:       onUpdate(float deltaTime)
--                  deltaTime: the cooldown time
--
-- RETURNS:         void
--
-- Called every game loop. dequeues all events from the entity's
-- controller and proceses those events
---------------------------------------------*/
void Vessel::onUpdate(float deltaTime)
{
	float val;

	attCool += deltaTime;
	sf::Time elapsedTime;
	sf::Time frameTime = sf::seconds(1.0/120);

	// TIME UPDATES
	elapsedTime = vesselClock.restart();

	//update left and right orientation
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		sprite->sprite().setScale(-1,1);
		direction = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sprite->sprite().setScale(1,1);
		direction = 1;
	}

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
				//std::cout << "Processing move message" << std::endl;
				MoveEvent* ev = (MoveEvent*) (*it);
				int xDir = ev->getXDir();
				int yDir = ev->getYDir();

				// set position to last known position on server to avoid
				// sync problems across the clients
	      		Entity::aMove(ev->getX(), ev->getY(), false);
				//	printf("vessel x, y: expected: %f %f actual: %f %f\n", ev->getX(), ev->getY(), getEntity()->left, getEntity()->top);

				if (yDir == -1)
				{
					newYSpeed -= ySpeed;

					if ( !runAnim->isRunning() )
					{
						runAnim->run(true);
						runAnim_mask->run(true);
						runAnim_wep->run(true);
					}
				}
				else if (yDir == 1)
				{
					newYSpeed += ySpeed;

					if ( !runAnim->isRunning() )
					{
						//runAnim->run(true);
						runAnim->run(true);
						runAnim_mask->run(true);
						runAnim_wep->run(true);
					}
				}
				else if (xDir == 1)
				{
					newXSpeed += xSpeed;

					if ( !runAnim->isRunning() )
					{
						//runAnim->run(true);
						runAnim->run(true);
						runAnim_mask->run(true);
						runAnim_wep->run(true);
					}
				}
				else if (xDir == -1)
				{
					newXSpeed -= xSpeed;

					if ( !runAnim->isRunning() )
					{
						//runAnim->run(true);
						runAnim->run(true);
						runAnim_mask->run(true);
						runAnim_wep->run(true);
					}
				}
			break;
			}

			case ::Marx::ATTACK:
			{
				if (Manager::ProjectileManager::getServer())
				{
					if (attCool >= ATTACK_COOLDOWN)
					{
						AttackEvent* aev = (AttackEvent*) (*it);
						createAttack(*aev, atk_sprite, left, top);
						attCool = 0;
					}
				}
				else
					playAttackSound();

                break;
			}
			case ::Marx::SK_ATTACK:
			{
				if (Manager::ProjectileManager::getServer())
				{
					if (attCool >= ATTACK_COOLDOWN)
					{
						SkillAttackEvent* saev = (SkillAttackEvent*) (*it);
						createSkAttack(*saev, satk_sprite, left, top);
						attCool = 0;
					}
				}
				else
					playAttackSound();

                break;
			}
            case ::Marx::SET_HEALTH:
            {
                SetHealthEvent* ev = (SetHealthEvent*) (*it);
				std::cout << "Vessel:: set health" << std::endl;
                setHealth(getHealth() - ev->getChange());
				playHurtSound();
				std::cout << "Vessel:: Health = " << currentHealth << std::endl;
				if(currentHealth <= 0)
				{
					std::cout << "Vessel Dead:" << std::endl;
					onDestroy();
				}
                break;
            }
			case ::Marx::UPDATE:
			{
				UpdateEvent* ev = (UpdateEvent*) (*it);
				myX = left;
				myY = top;

				servX = ev->_x;
				servY = ev->_y;

				Entity::aMove(ev->_x, ev->_y, false);
                break;
			}
			case ::Marx::SKILL:
			{
				// process the skill event, and increase/decrease hp and stuff
				SkillEvent *ev = (SkillEvent*)(*it);

				switch(ev->getSkillType())
				{
					case SKILLTYPE::HEAL:
						currentHealth += ev->getValue();
						if (myHealthBar) myHealthBar->update((float)currentHealth/(float)maxHealth);
					break;
					case SKILLTYPE::DMG:
						currentHealth -= ev->getValue();
						if (myHealthBar) myHealthBar->update((float)currentHealth/(float)maxHealth);
						playHurtSound();
					break;
					case SKILLTYPE::BUFF:
						val = ((float)ev->getValue()) / 100.0;

						xSpeed += val;
						ySpeed += val;
					break;
					case SKILLTYPE::DEBUFF:
						val = ((float)ev->getValue()) / 100.0;

						xSpeed -= val;
						ySpeed -= val;
					break;
					case SKILLTYPE::BIGHEAL:
						currentHealth += ev->getValue();
						if (myHealthBar) myHealthBar->update((float)currentHealth/(float)maxHealth);
					break;
					case SKILLTYPE::SPAWN:
						// Vessel implementation not needed
					break;
				}

				break;
			}
			case ::Marx::ADD_POINTS:
			{
				if (Manager::ProjectileManager::getServer())
				{
					std::cout << "Add points " << std::endl;
					AddPointsEvent *pointsEvent = (AddPointsEvent*) (*it);
					if (player != NULL)
						player->givePoints(pointsEvent->getPoints());
					break;
				}
			}
		}
	}

	if ( elapsedTime > frameTime )
	{
			runAnim->update(frameTime);
			runAnim_mask->update(frameTime);
			runAnim_wep->update(frameTime);
	}

	//if x speed and y speed are 0, stop animation
	if ( ( newXSpeed == 0 ) && ( newYSpeed == 0) )
	{
		runAnim->pause(true);
		runAnim_mask->pause(true);
		runAnim_wep->pause(true);
	}

	if(currentHealth <= 0)
	{
		std::cout << "Moving GateKeeper to ambiguous destination!!" << std::endl;
		onDestroy();
	}

	getController()->clearEvents();


// Needs improvement?
/*	if (std::abs(servX - myX) > 1 || std::abs(servY - myY) > 1)
	{
		float syncX = myX - (deltaTime * (myX - servX));
		float syncY = myY - (deltaTime * (myY - servY));

		Entity::aMove(syncX, syncY, false);
	}

	else if (std::abs(servX - myX) > 0.5 || std::abs(servY - myY) > 0.5)
	{
		Entity::aMove(servX, servY, false);
	}*/

	playFootstepSound();
	Entity::rMove(newXSpeed, newYSpeed,false);

}

void Vessel::setPlayerEntity(PlayerEntity *entity)
{
	player = entity;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	playFootstepSound
--
-- DATE:		April 7, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE:	void Vessel::playFootstepSound()
--
-- RETURNS: 	void
--
-- NOTES:       Plays Vessel footstep sounds. Sound changes depending on grass or stone floor.
-----------------------------------------------------------------------------------------------*/
void Vessel::playFootstepSound()
{
	static bool soundActive = false;
	static BlockZone steppedTile = GRASS;

	// Sounds for walking:
	// first get the tile type we're walking on
	Cell* footstepTile = *getCell().begin();
	sf::Vector2f soundPos(left + newXSpeed, top + newYSpeed);
	footstep.setPosition(left + newXSpeed, top + newYSpeed, 0);  // this line prevent's player character's
	 															 // footsteps from fading & being off-center
	footstep.setMinDistance(3.0);

	if (footstepTile->getTileId() >= GRASS_TL && footstepTile->getTileId() <= GRASS_BR)
	{
		// we need the extra soundActive boolean to make sure we're not playing a new
		// sound when there's already a walking sound active for our vessel
		if (((newXSpeed != 0 || newYSpeed != 0) && !soundActive) ||
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
		if (((newXSpeed != 0 || newYSpeed != 0) && !soundActive) ||
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
	// stop all sounds of walking if walking speed is (0, 0)
	if ((newXSpeed == 0 && newYSpeed == 0) && soundActive)
	{
		footstep.stop();
		soundActive = false;
	}
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	playHurtSound
--
-- DATE:		April 7, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE:	void Vessel::playHurtSound()
--
-- RETURNS: 	void
--
-- NOTES:       Plays the sound of Vessel getting hurt.
-----------------------------------------------------------------------------------------------*/
void Vessel::playHurtSound()
{
	sf::Vector2f soundPos(left + newXSpeed, top + newYSpeed);
	voice.setPosition(left + newXSpeed, top + newYSpeed, 0);  // this line prevent's player character's
															  // voice from fading & being off-center
	voice.setMinDistance(3.0);
	voice = SoundManager::play(hurtSound, soundPos);
	voice.play();
	//printf("Hurt sound should play\n");
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:	playAttackSound
--
-- DATE:		April 7, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Sanders Lee
--
-- PROGRAMMER:	Sanders Lee
--
-- INTERFACE:	void Vessel::playAttackSound()
--
-- RETURNS: 	void
--
-- NOTES:       Plays the sound of Vessel attacking.
-----------------------------------------------------------------------------------------------*/
void Vessel::playAttackSound()
{
	sf::Vector2f soundPos(left + newXSpeed, top + newYSpeed);
	voice.setPosition(left + newXSpeed, top + newYSpeed, 0);  // this line prevent's player character's
															  // voice from fading & being off-center
	voice.setMinDistance(3.0);
	voice = SoundManager::play(attackSound, soundPos);
	voice.play();
	//printf("Attack sound should play\n");
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
    footstep.stop();

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
	sf::Vector2f soundPos(left, top);
	voice.stop();
	//voice = SoundManager::play(hurtSound, soundPos);
	//voice.setLoop(true);
	//voice.play();

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
--		Marc Rafanan
--		Jonathan Chu
--
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
	return (currentHealth <= 0);
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
-- FUNCTION:	setHealth
--
-- DATE:		April 7, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Calvin Rempel, Melvin Loho
--
-- PROGRAMMER:	Calvin Rempel, Melvin Loho
--
-- INTERFACE:	void setHealth(int health)
--				int attack: the amount to set health to
--
-- RETURNS:		nothing
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

    if (myHealthBar) myHealthBar->update((float)currentHealth/(float)maxHealth);
}

void Vessel::setSpeed(int _speed)
{
	travelSpeed = _speed;
}

int Vessel::getSpeed()
{
	return travelSpeed;
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
-- FUNCTION: stopAllSounds
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Calvin Rempel
--
-- PROGRAMMER:	Calvin Rempel
--
-- INTERFACE: void stopAllSounds()
--
-- RETURNS: void
--
-- NOTES:
-- Stops all sounds played by the vessel
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::stopAllSounds()
{
    footstep.stop();
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

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:	setHealthBar
--
-- DATE:		April 7, 2015
--
-- REVISIONS:	(Date and Description)
--
-- DESIGNER:	Melvin Loho
--
-- PROGRAMMER:	Melvin Loho
--
-- INTERFACE:	void Vessel::setHealthBar(GUI::HealthBar* hb)
--				hb: the health bar that this Vessel will use
--
-- RETURNS:		void
--
-- NOTES:
-- This function associates the specified health bar with this Vessel.
----------------------------------------------------------------------------------------------------------------------*/
void Vessel::setHealthBar(GUI::HealthBar* hb)
{
	myHealthBar = hb;
}
