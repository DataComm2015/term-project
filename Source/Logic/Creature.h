#ifndef _CREATURE_H_
#define _CREATURE_H_

#include "../Engine/Entity.h"

using Marx::Entity;

/*
 * This Class provides a common interface for all "creature" in the game
 * including the player. This allows them to be buffed/debuffed identically.
 *
 * PROGRAMMER: Calvin Rempel
 */
class Creature
{
    public:
        virtual void setHealth(int health);
        virtual void setAttack(int attack);
        virtual Entity *getEntity();
};

#endif
