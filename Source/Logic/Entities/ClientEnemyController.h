/*#ifndef _CLIENT_ENEMY_CONTROLLER_H_
#define _CLIENT_ENEMY_CONTROLLER_H_

#include "ClientNetworkController.h"
#include "../EnemyControllerInit.h"
#include "../GameScene.h"
#include "../EntityFactory.h"
#include "../Creature.h"

class ClientEnemyController : public ClientNetworkController
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
*/
