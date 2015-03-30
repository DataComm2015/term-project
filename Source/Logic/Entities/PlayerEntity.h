#ifndef _PLAYER_ENTITY_H_
#define _PLAYER_ENTITY_H_

#include "../../Engine/Controller.h"
#include "../../Network/Session.h"
#include "../../Network/Message.h"
#include "../../Network/NetworkEntity.h"
#include "../PlayerMode.h"
#include "../PlayerLobbyChoices.h"
#include "ServerCommandEntity.h"

class ServerCommand;

using Networking::NetworkEntity;
using Networking::Session;
using Networking::Message;

/**
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
        PLAYER_MODE getMode();

        void setController(ServerCommandEntity* controller);
        void unsetController();

    protected:
        virtual void onUnregister(Session* session, Message msg);
        virtual void onUpdate(Message msg);
        void clearControllerEvents();

    private:
        ServerCommandEntity* controller;
        ServerCommand *server;
        PLAYER_MODE mode;
        PlayerLobbyChoices lobbyChoices;
};

#endif
