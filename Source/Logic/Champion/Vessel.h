/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: VesselClass.cpp
--
-- PROGRAM: 4981 game project
--
-- FUNCTIONS:
--     Vessel( job_class jobclass, GameMap gmap, int x, int y );
--     ~Vessel();
--
--     void setPosition( int x, int y );
--
--     void resetEXP();
--     void increaseEXP( int exp );
--     int  getEXP();
--     int  getNextLevelEXP();
--
--     int  getLevel();
--     void increaseLevel();
--
--     void resetHP();
--     void increaseHP( int hp );
--     void decreaseHP( int hp );
--     int  getHP();
--     int  getMaxHP();
--
--     void resetAttackPower();
--     void attackPowerUp( int attackpower );
--     void attackPowerDown( int attackpower );
--     int  getAttackPower();
--     int  getDefaultAttackPower();
--
--     void resetSpeed();
--     void speedUp( int speed );
--     void speedDown( int speed );
--     int  getSpeed();
--     int  getDefaultSpeed();
--
--     bool checkDeath();
--     void die();
--
--     void move( int direction );
--
--     void normalAttack( int x, int y );
--     void useAbility( int abilityNum );
--
-- DATE: February 15, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Sanders Lee
--
-- PROGRAMMER: Sanders Lee
--
-- NOTES:
-- This class file provides the functions needed to set up and modify Vessel status.
-- It also provides the functions to control a Vessel (movement and attack).
----------------------------------------------------------------------------------------------------------------------*/
#ifndef VESSEL_H
#define VESSEL_H

#include <SFML/Graphics.hpp>
#include "../../Engine/Map.h"
#include "../../Engine/Entity.h"

#define MAX_LEVEL 10;

typedef char Weapon;
typedef char Ability;

typedef enum job_class { WARRIOR, SHAMAN, HUNTER, SCOUT } job_class;

class Vessel : public Marx::Entity
{
	protected:
		job_class jobClass;
		int currentEXP;
		int nextLevelEXP;
		int currentLevel;
		float xPosition;
		float yPosition;
		int currentHealth;
		int maxHealth;
		float travelSpeed;
		float defaultSpeed;
		float xSpeed;
		float ySpeed;
		int currentAttackPower;
		int defaultAttackPower;
		float currentAttackCoolDown;
		float maxAttackCooldown;
		int direction;	//0 = right, 1 = left
		bool moving;
		Ability* abilities;	//3 abilities for each Vessel
		//TO DO: pointer to the game map needed in the future

	public:
		Vessel( Marx::Map *gmap, job_class jobClass, Ability* abilityList, float x, float y );
		~Vessel(); //not virtual?

		job_class getJobClass();

		void  setPosition( float x, float y );
		float getXPosition();
		float getYPosition();

		void resetEXP();
		void increaseEXP( int exp );
		int  getEXP();
    int  getNextLevelEXP();
		int  getLevel();

		void resetHP();
		void increaseHP( int hp );
		void decreaseHP( int hp );
		int  getHP();
		int  getMaxHP();

		void resetAttackPower();
		void attackPowerUp( int attackPower );
		void attackPowerDown( int attackPower );
		int  getAttackPower();
		int  getDefaultAttackPower();

		void  resetSpeed();
		void  speedUp( float speed );
		void  speedDown( float speed );
		float getSpeed();
		float getDefaultSpeed();

		float getXSpeed();
		float getYSpeed();
		bool  isMoving();
		int   getDirection();

		bool checkDeath();
		void die();

		void detectMove();
		void move();
		void stop( int key );

		void normalAttack( float x, float y );
		void useAbility( int abilityNum, float x, float y );
		void coolDownAttack( float delta_t );
};

#endif
