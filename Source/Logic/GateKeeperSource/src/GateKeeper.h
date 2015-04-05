#ifndef GATEKEEP_H
#define GATEKEEP_H
/********************************************************************************
**	SOURCE FILE:	GateKeeper.h -  		Header file for The gatekeeper npc base
**											class. Contains function prototypes
**
**	PROGRAM:	Term_Project
**
**	DATE: 		February 15, 2015
**
**
**	DESIGNER: 	Filip Gutica A00781910
**
**	PROGRAMMER: Filip Gutica A00781910
**				Sanders Lee
**
***********************************************************************************/

#include <SFML/Graphics.hpp>
#include "../../../Engine/VEntity.h"
#include "../../../Engine/Map.h"
#include "../../../Engine/Cell.h"
#include "../../../Engine/Controller.h"
#include "../../Creature.h"
#include "../../../Engine/TileManager.h"
#include "../../../Multimedia/manager/SoundManager.h"

class GateKeeper : public Marx::VEntity, public Creature
{

	public:
		GateKeeper(SGO &sprite,
			Marx::Map* map,
			float x,
			float y,
			Marx::Controller* ctrl,
			float h,
			float w
		);
		virtual ~GateKeeper();
		virtual void detectPlayers();
		virtual void enterCombat();
		virtual void leaveCombat();
		virtual bool inCombatRange();
		virtual void setRange(int r);
		virtual void setHealth(int h);
		virtual void setAttack(int a);
		virtual void setAttackSpeed(int as);
		virtual void setMovementSPed(int ms);
		virtual void setTarget(/*Player*/);
		virtual void setCooldown(/*Timer*/);
		virtual void setPosition(float x, float y);
		virtual void setXSpeed(float x);
		virtual void setYSpeed(float y);
		virtual int getRange();
		virtual int getHealth();
		virtual int getAttack();
		virtual int getAttackSpeed();
		virtual int getMovementSpeed();
		//virtual Vessel getTarget();
		virtual time_t getCooldown();
		virtual void turn();
		virtual void onCreate();
		virtual void onDestroy();
		virtual void onUpdate(float);
		virtual bool operator==(const VEntity&);
    virtual Entity* getEntity();
		virtual bool isMoving();



	protected:
		bool movingLeft;
    bool movingRight;
		bool movingUp;
    bool movingDown;
		int _range;
		int _type;
		int _health;
		int _attack;
		int _attackSpeed;
		int _movementSpeed;
		float _xSpeed;
		float _ySpeed;
		float newXSpeed = 0;
		float newYSpeed = 0;
		int _direction;
		float _xPos;
		float _yPos;
		bool _incombat;
		bool _moving;
		Marx::Controller* _ctrl;
		time_t _cooldown;
		id_resource grassWalkSound, stoneWalkSound, hurtSound, attackSound;

	private:
		sf::Sound footstep;
		sf::Sound voice;
		//Player _target;
		//PatrolRadius _radius;
		//Timer _cooldownTimer;
		//AI _ai;



};
#endif
