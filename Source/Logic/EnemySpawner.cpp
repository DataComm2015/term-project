#include "EnemySpawner.h"

#include "Creature.h"

Creature *EnemySpawner::createEnemy(ENEMY_TYPES type, Marx::Controller *controller,Marx::Map *map, float x, float y)
{
    Creature *creature = NULL;

    switch(type)
    {
        case I_DONT_KNOW:
            // CREATE NEW ENEMY OF GIVEN TYPE
            // RETURN ENEMY
            break;
            
        default:
            break;
    }
    
    return creature;
}
