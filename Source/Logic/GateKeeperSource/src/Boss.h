/********************************************************************************
**	SOURCE FILE:	Boss.h -  			Header file for The boss npc class. 
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

class Boss : public GateKeeper
{
	public:
		Boss(GKstruct *gk) : GateKeeper(*gk);
		void updateNPC();
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
		void specialAbility();
	
};