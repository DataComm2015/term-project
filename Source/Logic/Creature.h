#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "Event.h"
#include "../Engine/Entity.h"
#include "../Engine/Controller.h"
#include "../Engine/Action.h"
#include "../Engine/ProjectileManager.h"
#include "EntityTypes.h"

using Marx::Entity;

/*
 * This Class provides a common interface for all "creature" in the game
 * including the player. This allows them to be buffed/debuffed identically.
 *
 * PROGRAMMER: Calvin Rempel
 *			Thomas Tallentire
 *      Marc Vouve
 */
class Creature
{
    public:
        Creature();
        ~Creature();
        virtual int getHealth();
        virtual void setHealth(int _health);
        virtual int getSpeed();
        virtual void setSpeed(int _speed);
        virtual void setAttack(int attack);
		virtual int getAttack();
		virtual Marx::Projectile* createAttack(AttackEvent&, SGO &sprite, float x, float y);
		virtual Marx::Projectile* createSkAttack(SkillAttackEvent& event, SGO &sprite, float x, float y);
        virtual void stopAllSounds() = 0;
        virtual Entity * getEntity();
	protected:
		std::map<enum ActionType, Marx::Action*> actionList;
};

#endif
