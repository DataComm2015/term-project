/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: VesselClass.cpp
--
-- PROGRAM: 4981 game project
--
-- FUNCTIONS:
--	    VesselVessel( SGO& _sprite, SGO _mask, SGO _weapon, Marx::Map * gmap,
--			float x, float y, Marx::Controller* controller, float height, float width);
-- 	    virtual ~Vessel();
--		virtual void onUpdate(float);
--     	void setPosition( int x, int y );
--
--  	void playFootstepSound();
-- 		void playHurtSound();
-- 		void playAttackSound();
--
-- 		void setPlayerEntity(PlayerEntity *entity);
--
-- 		void setPosition( float x, float y );
-- 		float getXPosition();
-- 		float getYPosition();
--
-- 		int getXSpeed();
-- 		int getYSpeed();
-- 		bool isMoving();
-- 		int getDirection();
--
-- 		void resetEXP();
-- 		void increaseEXP( int exp );
-- 		int  getEXP();
--		int  getNextLevelEXP();
-- 		int  getLevel();
-- 		void increaseLevel();
--
-- 		job_class getJobClass();
--
-- 		void resetHP();
-- 		void increaseHP( int hp );
-- 		void decreaseHP( int hp );
-- 		int  getMaxHP();
--
-- 		void resetAttackPower();
-- 		void attackPowerUp( int attackpower );
-- 		void attackPowerDown( int attackpower );
-- 		int  getAttackPower();
-- 		int  getDefaultAttackPower();
--
-- 		void resetSpeed();
-- 		void speedUp( int speed );
-- 		void speedDown( int speed );
-- 		int  getDefaultSpeed();
--
-- 		bool checkDeath();
-- 		void die();
--
-- 		void move();
-- 		void stop(int key);
--
-- 		void normalAttack( int x, int y );
-- 		void useAbility( int abilityNum, int x, int y );
--
-- 		void setHealthBar(GUI::HealthBar* hb);
--
-- 		virtual int getHealth();
-- 		virtual void setHealth(int _health);
-- 		virtual int getSpeed();
-- 		virtual void setSpeed(int _speed);
-- 		virtual void setAttack(int attack);
-- 		virtual void stopAllSounds();
-- 		virtual Entity *getEntity();
-- 		ENTITY_TYPES getType();
--
-- DATE: February 15, 2015
--
-- REVISIONS: April 7, 2015 - Sanders Lee - Required functions have changed a bit
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
#include "../../Engine/VEntity.h"
#include "../../Engine/Cell.h"
#include "../../Engine/Controller.h"
#include "../../Engine/TileManager.h"
#include "../../Multimedia/graphics/Animation.h"
#include "../Creature.h"
#include "../EntityTypes.h"
#include "../../Multimedia/gui/HealthBar.h"
#include <SFML/Audio.hpp>


#define MAX_LEVEL 10;

typedef char Weapon;
typedef char Ability;

class PlayerEntity;

typedef enum job_class { WARRIOR, SHAMAN, HUNTER, SCOUT, TEGUH } job_class;


class Vessel : public Marx::VEntity, public Creature
{
	private:
		sf::Sound footstep;
		sf::Sound voice;
		//Animation *runAnim;
		//Animation *runAnim_mask;
		//Animation *runAnim_wep;
		SGO shadow;
		PlayerEntity *player;
		GUI::HealthBar* myHealthBar;

	protected:
		job_class jobClass;
		int currentHealth;
		int maxHealth;
		int currentEXP;
		int nextLevelEXP;
		int currentLevel;
		int defaultSpeed;
		int travelSpeed;
		int attackPower;
		float xSpeed;
		float ySpeed;
		float xPos;
		float yPos;
		float myX;
		float myY;
		float servX;
		float servY;
		float attCool;
		int direction;	//0 = right, 1 = left //why not a bool?
		bool movingLeft;
	    bool movingRight;
		bool movingUp;
	    bool movingDown;
		Ability* abilities;	//3 abilities for each Vessel
		SGO mask_sprite;
		SGO atk_sprite;
		SGO satk_sprite;
		SGO weapon_sprite;
		static id_resource grassWalkSound, stoneWalkSound, hurtSound, attackSound;
		//TO DO: pointer to the game map needed in the future

	public:
        float newXSpeed;
        float newYSpeed;
		Vessel( SGO& _sprite, SGO _mask, SGO _weapon,
						Marx::Map * gmap,
						float x,
						float y,
						Marx::Controller* controller,
						float height,
						float width
						/*, job_class jobClass, Ability* abilityList*/ );
		//inherited methods
		virtual ~Vessel();
		virtual void onUpdate(float);
		//virtual void draw(Renderer& renderer, sf::RenderStates states) const override;

		void playFootstepSound();
		void playHurtSound();
		void playAttackSound();

		void setPlayerEntity(PlayerEntity *entity);

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
		int  getMaxHP();

		void resetAttackPower();
		void attackPowerUp( int attackpower );
		void attackPowerDown( int attackpower );
		int  getAttackPower();
		int  getDefaultAttackPower();

		void resetSpeed();
		void speedUp( int speed );
		void speedDown( int speed );
		int  getDefaultSpeed();

		bool checkDeath();
		void die();

		void move();
		void stop(int key);

		void normalAttack( int x, int y );
		void useAbility( int abilityNum, int x, int y );

		void setHealthBar(GUI::HealthBar* hb);

        virtual int getHealth();
        virtual void setHealth(int _health);
        virtual int getSpeed();
        virtual void setSpeed(int _speed);
		virtual void setAttack(int attack);
        virtual void stopAllSounds();
		virtual Entity *getEntity();
		ENTITY_TYPES getType();
};

#endif
