/********************************************************************************
**	SOURCE FILE:	ServerEnemyController.h -  	Header file for the server enemy controller
**
**	PROGRAM:	Term_Project
**
**	DATE: 		February 15, 2015
**
**
**	DESIGNER: 	Calvin Rempel
                Filip Gutica
**
**	PROGRAMMER: Calvin Rempel
**              Filip Gutica
**
***********************************************************************************/
#ifndef _SERVER_ENEMY_CONTROLLER_H_
#define _SERVER_ENEMY_CONTROLLER_H_

#define THRESHOLD 0
#define AGGRO_RADIUS 30

#include "ServerNetworkController.h"
#include "../Artificial Intelligence/Behaviour.h"
#include "../GateKeeperSource/src/GateKeeper.h"
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
        void setEntity(GateKeeper*);
        void init();
        void updateBehaviour(float deltaTime);
        Vessel* detectVessels();
        float getDistance(float, float, float, float);

    private:
        Behaviour *behaviour;
        GateKeeper* _currEntity;
        ServerGameScene* _servGameScene;
        int prevX = 0;
        int prevY = 0;
        int xDirection;
        int yDirection;
        Vessel* targetVessel;
        bool moving;
        float attackTimer;
};

#endif
