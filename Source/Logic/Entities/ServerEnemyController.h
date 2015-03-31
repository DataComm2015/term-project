#ifndef _SERVER_ENEMY_CONTROLLER_H_
#define _SERVER_ENEMY_CONTROLLER_H_

#include "ServerNetworkController.h"

class Behaviour;

class ServerEnemyController : public ServerNetworkController
{
    public:
        ServerEnemyController(Behaviour *behaviour);
        virtual ~ServerEnemyController();

        void init();
        void updateBehaviour(float deltaTime);

    private:
        Behaviour *behaviour;
};

#endif
