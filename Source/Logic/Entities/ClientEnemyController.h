#ifndef _CLIENT_ENEMY_CONTROLLER_H_
#define _CLIENT_ENEMY_CONTROLLER_H_

#include "NetworkControllerEntity.h"
#include "../EnemyControllerInit.h"

class ClientEnemyController : public NetworkControllerEntity
{
    public:
        ClientEnemyController(int id, EnemyControllerInit *initData);
        ~ClientEnemyController();
        virtual void onUpdate( Message message );
};

#endif
