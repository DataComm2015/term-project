#ifndef MINION_H
#define MINION_H
/********************************************************************************
**	SOURCE FILE:	Minion.h -  		Header file for The Minion npc class.
**										Contains function prototypes
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
#include "GateKeeper.h"

class Minion : public GateKeeper
{
	public:
		Minion(Marx::Map* map, float x, float y, Marx::Controller* ctrl = NULL, float h = 1.0, float w = 1.0) :
			GateKeeper(map, x, y, ctrl, h, w);
		void detectPlayers();
		void enterCombat();
		void leaveCombat();
		bool inCombatRange();
		void setRange(int r);
		void setHealth(int h);
		void setAttack(int a);
		void setAttackSpeed(int as);
		void setMovementSPed(int ms);
		void setTarget(/*Player*/);
		void setCooldown(/*Timer*/);
		int getRange();
		int getHealth();
		int getAttack();
		int getAttackSpeed();
		int getMovementSpeed();
		Player getTarget();
		time_t getCooldown();

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

};

#endif
