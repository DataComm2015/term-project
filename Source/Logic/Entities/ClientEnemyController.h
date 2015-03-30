#ifndef _CLIENT_ENEMY_CONTROLLER_H_
#define _CLIENT_ENEMY_CONTROLLER_H_

#include "NetworkControllerEntity.h"
#include "../EnemyControllerInit.h"
#include "../GameScene.h"
#include "../EnemySpawner.h"
#include "../Creature.h"

class ClientEnemyController : public NetworkControllerEntity
{
    public:
        ClientEnemyController(int id, EnemyControllerInit *initData, GameScene *gs);
        ~ClientEnemyController();
        virtual void onUpdate( Message message );
    private:
    	GameScene *gameScene;
    	Creature *enemy;
};

#endif
