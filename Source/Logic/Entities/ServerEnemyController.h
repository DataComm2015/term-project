#ifndef _SERVER_ENEMY_CONTROLLER_H_
#define _SERVER_ENEMY_CONTROLLER_H_

#include "ServerNetworkController.h"
#include "../Artificial Intelligence/Behaviour.h"
#include "../Event.h"

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
        bool moving;
};

#endif
