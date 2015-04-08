#ifndef _PLAYER_ENTITY_H_
#define _PLAYER_ENTITY_H_

#include "../../Engine/Controller.h"
#include "../../Network/Session.h"
#include "../../Network/Message.h"
#include "../../Network/NetworkEntity.h"
#include "../PlayerMode.h"
#include "../PlayerLobbyChoices.h"
#include "../Skills.h"
#include "../ServerGameScene.h"
#include "ServerNetworkController.h"

class ServerCommand;
class Vessel;

using Networking::NetworkEntity;
using Networking::Session;
using Networking::Message;

/**
 * CLASS:       PlayerEntity : public NetworkEntity
 *
 * DESIGNER:    ???
 *
 * PROGRAMMER:  ???
 *              Sanders Lee
 *
 * NOTES:
 * the {Player} is resides the server, and is logically mapped to the {Command}
 *   class over the network, which is on the client side.
 *
 * the client sends command using {Command::update} such as move commands or
 *   others like choosing their character to the Server. such commands are
 *   handled in the {Player::onUpdate} method. and sent using the.
 */
class PlayerEntity : public NetworkEntity
{
    public:
        PlayerEntity(ServerCommand *server);
        virtual ~PlayerEntity();

        void setMode(PLAYER_MODE mode);
        void setType(PLAYER_TYPE type); // Sets the player type - Sanders Lee
        PLAYER_MODE getMode();
        PLAYER_TYPE getType(); // Gets the player type - Sanders Lee

        void setController(ServerNetworkController* controller);
        void unsetController();
        char* getNickname();
        float getDistance(float, float, float, float);
        void setSGameScene(ServerGameScene *ref);
		void setVessel(Vessel *vessel);
		Vessel *getVessel();
		void givePoints(float points);
		float getPoints();
        void skillCaseHandler(Message msg);
        void sendNotification(skill *sk);
        void clearControllerEvents();

    protected:
        virtual void onUnregister(Session* session, Message msg);
        virtual void onUpdate(Message msg);

    private:
        char* nickname;
        ServerGameScene *serverRef;
        ServerNetworkController* controller;
        ServerCommand *server;
        PLAYER_MODE mode;
        PLAYER_TYPE type;
        PlayerLobbyChoices lobbyChoices;
		Vessel *vessel;
		float points;
};

#endif
