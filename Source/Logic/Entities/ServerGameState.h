#ifndef _SERVER_GAME_STATE_H_
#define _SERVER_GAME_STATE_H_

#include "../../Network/NetworkEntity.h"
#include "../../Network/Message.h"
#include "../../Network/Session.h"

#include <map>

using Networking::Session;
using Networking::Message;

class ServerCommand;
class PlayerEntity;

class ServerGameState : public Networking::NetworkEntity
{
    public:
        ServerGameState(ServerCommand *command);
        virtual ~ServerGameState();

        void playerJoined(Session *session, PlayerEntity *player);
        void playerLeft(Session *session);

        void startLobbyCountdown(int remainingTime);
        void stopLobbyCountdown(int remainingTime);

        std::map<Session*, PlayerEntity*> getPlayers();
        void goToLobby();
        void goToGame(bool inProgress);

    protected:
        virtual void onUnregister(Networking::Session *session,
                                  Networking::Message message);
        virtual void onUpdate(Networking::Message message);
        
        ServerCommand *command;
    	std::map<Session*, PlayerEntity*> players;
};

#endif