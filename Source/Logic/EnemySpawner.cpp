#include "EnemySpawner.h"
#include "Creature.h"

id_resource gkSprite;
SGO gkSGO;


Creature *EnemySpawner::createEnemy(ENEMY_TYPES type, Marx::Controller *controller,Marx::Map *map, float x, float y)
{
    Creature *creature = NULL;

    gkSprite = Manager::TextureManager::store(
  		Manager::TextureManager::load("Assets/Art/Misc/placeholder_32.png")
    );

    gkSGO.sprite().setTexture(*Manager::TextureManager::get(gkSprite));
  	gkSGO.sprite().setTextureRect(sf::IntRect(0, 0, 32, 32));
  	gkSGO.sprite().setScale(2, 2);
  	gkSGO.middleAnchorPoint(true);



    switch(type)
    {
        case BASIC_TYPE:
            creature = new GateKeeper(gkSGO, map, x, y, controller, 1, 1);

            break;
        case I_DONT_KNOW:
            // CREATE NEW ENEMY OF GIVEN TYPE
            // RETURN ENEMY
            break;

        default:
            break;
    }

    return creature;
}
