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
		void setAttackSpeed(int as);
		void setXSpeed(float x);
		void setYSpeed(float y);
    void setSpeed(int _speed);
		int getRange();
		int getHealth();
		int getAttack();
		int getAttackSpeed();
		int getMovementSpeed();
    int getSpeed();
		void turn();
		void onCreate();
		void onUpdate(float);
		bool operator==(const VEntity&);
  	void stopAllSounds();
    Entity* getEntity();
	  bool isMoving();
		void playSound(float, float);
		void animate();

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
		sf::Sound footstep;
		sf::Sound voice;
		BlockZone steppedTile;
		bool soundActive;
		Animation *gkAnimation;

};

#endif
