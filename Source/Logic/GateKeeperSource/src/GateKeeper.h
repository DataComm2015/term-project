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
#include "../../../Multimedia/graphics/Animation.h"

class GateKeeper : public Marx::VEntity, public Creature
{

	public:
		GateKeeper(SGO& sprite,
			Marx::Map* map,
			float x,
			float y,
			Marx::Controller* ctrl,
			float h,
			float w
		);
		virtual ~GateKeeper();
		virtual void setRange(int r);
		virtual void setHealth(int h);
		virtual void setAttack(int a);
		virtual void setAttackSpeed(float as);
		virtual void setXSpeed(float x);
		virtual void setYSpeed(float y);
        virtual void setSpeed(int _speed);
		virtual int getRange();
		virtual int getHealth();
		virtual int getAttack();
		virtual float getAttackSpeed();
		virtual int getMovementSpeed();
        virtual int getSpeed();
		virtual void turn();
		virtual void onCreate();
		virtual void onUpdate(float);
		virtual bool operator==(const VEntity&);
        virtual void stopAllSounds();
    virtual Entity* getEntity();
		virtual bool isMoving();
		virtual void playSound(float, float);
		virtual void animate();
        ENTITY_TYPES getType();


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
		float _atackTimer;
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
