#ifndef _SERVER_GAME_STATE_H_
#define _SERVER_GAME_STATE_H_

#include "../../Network/NetworkEntity.h"
#include "../../Network/Message.h"
#include "../../Network/Session.h"

class ServerCommand;

class ServerGameState : public Networking::NetworkEntity
{
    public:
        ServerGameState(ServerCommand *command);
        virtual ~ServerGameState();

        void playerJoined(int numPlayers);
        void playerLeft(int numPlayers);

        void startLobbyCountdown(int remainingTime);
        void stopLobbyCountdown(int remainingTime);

        void goToLobby();
        void goToGame(bool inProgress);

    protected:
        virtual void onUnregister(Networking::Session *session,
                                  Networking::Message message);
        virtual void onUpdate(Networking::Message message);
        
        ServerCommand *command;
};

#endif
