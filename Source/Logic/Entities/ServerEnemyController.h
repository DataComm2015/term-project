#ifndef _SERVER_ENEMY_CONTROLLER_H_
#define _SERVER_ENEMY_CONTROLLER_H_

#define THRESHOLD 0
#define AGGRO_RADIUS 30

#include "ServerNetworkController.h"
#include "../Artificial Intelligence/Behaviour.h"
#include "../Event.h"
#include "../../Engine/VEntity.h"
#include "../ServerGameScene.h"

using Marx::Entity;

class Behaviour;

class ServerEnemyController : public ServerNetworkController
{
    public:
        ServerEnemyController(Behaviour *behaviour, ServerGameScene*);
        virtual ~ServerEnemyController();
        void setEntity(Entity*);
        void init();
        void updateBehaviour(float deltaTime);
        Vessel* detectVessels();
        float getDistance(float, float, float, float);

    private:
        Behaviour *behaviour;
        Entity* _currEntity;
        ServerGameScene* _servGameScene;
        int prevX = 0;
        int prevY = 0;
        int xDirection;
        int yDirection;
        Vessel* targetVessel;
        bool moving;
};

#endif
