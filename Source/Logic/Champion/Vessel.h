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
#include "../../Engine/Cell.h"
#include "../../Engine/Controller.h"

#define MAX_LEVEL 10;

typedef char Weapon;
typedef char Ability;

typedef enum job_class { WARRIOR, SHAMAN, HUNTER, SCOUT, TEGUH } job_class;

class Vessel : public Marx::Entity
{
	protected:
		job_class jobClass;
		int currentHealth;
		int maxHealth;
		int currentEXP;
		int nextLevelEXP;
		int currentLevel;
		int defaultSpeed;
		int travelSpeed;
		float xPosition;
		float yPosition;
		int xSpeed;
		int ySpeed;
		int direction;	//0 = right, 1 = left //why not a bool?
		bool moving;
		Weapon* weapon;
		Ability* abilities;	//3 abilities for each Vessel
		//TO DO: pointer to the game map needed in the future

	public:
		Vessel( Marx::Map *gmap, Marx::Controller* controller, job_class jobClass, Ability* abilityList, float x, float y );

		//inherited methods
		virtual ~Vessel();
		virtual void onUpdate();
		virtual void turn();
		virtual Marx::Entity* move(float, float, bool);
		virtual std::set<Marx::Cell*> getCell();
		virtual void onCreate();
		virtual void onDestroy();

		const Marx::Controller* _controller;

		void setPosition( float x, float y );
		float getXPosition();
		float getYPosition();

		int getXSpeed();
		int getYSpeed();
		bool isMoving();
		int getDirection();

		void resetEXP();
		void increaseEXP( int exp );
		int  getEXP();
    int  getNextLevelEXP();
		int  getLevel();
		void increaseLevel();

		job_class getJobClass();

		void resetHP();
		void increaseHP( int hp );
		void decreaseHP( int hp );
		int  getHP();
		int  getMaxHP();

		void resetAttackPower();
		void attackPowerUp( int attackpower );
		void attackPowerDown( int attackpower );
		int  getAttackPower();
		int  getDefaultAttackPower();

		void resetSpeed();
		void speedUp( int speed );
		void speedDown( int speed );
		int  getSpeed();
		int  getDefaultSpeed();

		bool checkDeath();
		void die();

		void detectMove();
		void move();
		void stop(int key);

		void normalAttack( int x, int y );
		void useAbility( int abilityNum, int x, int y );
};

#endif
