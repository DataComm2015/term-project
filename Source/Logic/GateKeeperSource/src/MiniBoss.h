#ifndef MINI_H
#define MINI_H
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

class MiniBoss : public GateKeeper
{
	public:
		MiniBoss(SGO& sprite,
			Marx::Map* map,
			float x,
			float y,
			Marx::Controller* ctrl,
			float h,
			float w
		);
		~MiniBoss();
		void setRange(int r);
		void setHealth(int h);
		void setAttack(int a);
		void setAttackSpeed(float as);
		void setXSpeed(float x);
		void setYSpeed(float y);
    void setSpeed(int _speed);
		float getXSpeed();
		float getYSpeed();
		int getRange();
		int getHealth();
		int getAttack();
		float getAttackSpeed();
    int getSpeed();
		void turn();
		void onCreate();
		void onUpdate(float);
		bool operator==(const VEntity&);
  		void stopAllSounds();
    	Entity* getEntity();
	  	bool isMoving();
		void playTravelSound(float, float);
		void playHurtSound();
		void playAttackSound();
		void animate();
		void processMoveEvent(MoveEvent* ev);
		void processSkillEvent(SkillEvent* ev);
		void processSetHealthEvent(SetHealthEvent* ev);
		void processAttackEvent(AttackEvent* aev);

		id_resource grassWalkSoundMBoss;
		id_resource stoneWalkSoundMBoss;
		id_resource hurtSoundMBoss;
		id_resource attackSoundMBoss;

	protected:
		bool movingLeft;
    	bool movingRight;
		bool movingUp;
    	bool movingDown;
		int _range;
		int _type;
		int _health;
		int _attack;
		float _attackSpeed;
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
		sf::Sound footstep;
		sf::Sound voice;
		BlockZone steppedTile;
		bool soundActive;
		Animation *gkAnimation;

	public:
		static const char *travelSnds[3];

		static const char *attackSnds[5];

		static const char *hurtSnds[4];

};

#endif
