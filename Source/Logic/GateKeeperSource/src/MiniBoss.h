#include "GateKeeper.h"

class MiniBoss : public GateKeeper
{
	public:
		MiniBoss(GKstruct *gk) : GateKeeper(*gk);
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
		void getRange();
		void getHealth();
		void getAttack();
		void getAttackSpeed();
		void getMovementSpeed();
		void getTarget();
		void getCooldown();

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