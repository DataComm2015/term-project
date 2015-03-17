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

struct GKstruct{
	int range;
	int type;
	int health;
	int attack;
	int attackSpeed;
	int movementSpeed;
	bool inCombat;
	//Player target
	//Patrol radius
	//Cooldown timer
	//AI object

}GKstruct;

class GateKeeper
{

	public:
		GateKeeper(GKstruct *gk);	//Initialize attributes from the GK struct
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
		virtual Player getTarget();
		virtual time_t getCooldown();
		
		
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