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
#include <SFML/Graphics.hpp>

typedef char Weapon;
typedef char Ability;

typedef enum job_class { WARRIOR, SHAMAN, HUNTER, SCOUT } job_class;

class Vessel
{
	protected:
		job_class jobClass;
		int currentHealth;
		int maxHealth;
		int currentEXP;
		int nextLevelEXP;
		int travelSpeed;
		int xPosition;
		int yPosition;
		int xSpeed;
		int ySpeed;
		int direction;	//0 = right, 1 = left //why not a bool?
		bool moving;
		Weapon* weapon;
		Ability* abilities;	//3 abilities for each Vessel
		//TO DO: pointer to the game map needed in the future

	public:
		Vessel( job_class jobClass, Ability* abilityList, int x, int y );
		~Vessel(); //not virtual?

		void setPosition( int x, int y );
		int getXPosition();
		int getYPosition();
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
