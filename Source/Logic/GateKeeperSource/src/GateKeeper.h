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
**
***********************************************************************************/

#include <SFML/Graphics.hpp>
#include "../../../Engine/VEntity.h"
#include "../../../Engine/Map.h"
#include "../../../Engine/Cell.h"
#include "../../../Engine/Controller.h"

class GateKeeper : public Marx::VEntity
{

	public:
		GateKeeper(SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl = NULL, float h = 1.0, float w = 1.0) :
			VEntity(sprite, map, x, y, ctrl, h, w)
			,_ctrl(ctrl)
			{
				_range = 1;
				_health = 100;
				_type = 1;
				_attack = 1;
				_attackSpeed = 1;
				_movementSpeed = 1;
				_incombat = false;
				_cooldown = 1;
				_xPos = x;
				_yPos = y;
				_xSpeed = 0;
				_ySpeed = 0;
				_moving = false;

			};

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
		virtual void onUpdate();
		virtual bool operator==(const VEntity&);


	private:
		int _range;
		int _type;
		int _health;
		int _attack;
		int _attackSpeed;
		int _movementSpeed;
		int _xSpeed;
		int _ySpeed;
		int _direction;
		float _xPos;
		float _yPos;
		bool _incombat;
		bool _moving;
		time_t _cooldown;
		//Player _target;
		//PatrolRadius _radius;
		//Timer _cooldownTimer;
		//AI _ai;

		Marx::Controller* _ctrl;

};
#endif
