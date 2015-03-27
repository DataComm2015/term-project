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
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include "../../../Engine/Entity.h"



class GateKeeper : public Marx::Entity
{

	public:
		GateKeeper(Marx::Map* map, float x, float y, Marx::Controller* ctrl = NULL, float h = 1.0, float w = 1.0) :
			Entity(map, x, y, ctrl, h, w)
			,_ctrl(ctrl) {};
		virtual ~GateKeeper();
		virtual void updateNPC();
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
		virtual int getRange();
		virtual int getHealth();
		virtual int getAttack();
		virtual int getAttackSpeed();
		virtual int getMovementSpeed();
		//virtual Vessel getTarget();
		virtual time_t getCooldown();

		virtual void turn();
		virtual std::set<Cell*> getCell();
		virtual void onCreate();
		virtual void onDestroy();
		virtual void onUpdate();
		virtual bool operator==(const Entity&);


	private:
		int _range;
		int _type;
		int _health;
		int _attack;
		int _attackSpeed;
		int _movementSpeed;
		bool _incombat;
		//Player _target;
		//PatrolRadius _radius;
		//Timer _cooldownTimer;
		//AI _ai;

		Marx::Controller* _ctrl;

};
