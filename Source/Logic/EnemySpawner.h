#ifndef _ENEMY_SPAWNER_H_
#define _ENEMY_SPAWNER_H_

#include "EnemyTypes.h"
#include "../Engine/Map.h"
#include "../Engine/Controller.h"
#include "GateKeeperSource/src/GateKeeper.h"

class Creature;

/*
 * EnemySpawner produces an Enemy of a specified ENEMY_TYPE.
 */
class EnemySpawner
{
    public:
        static Creature *createEnemy(ENEMY_TYPES type, Marx::Controller *controller, Marx::Map *map, float x, float y);
};

#endif
