#ifndef _SERVER_ENEMY_CONTROLLER_H_
#define _SERVER_ENEMY_CONTROLLER_H_

#include "ServerCommandEntity.h"

class Behaviour;

class ServerEnemyController : public ServerCommandEntity
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
