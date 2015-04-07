#ifndef _SERVER_GAME_STATE_H_
#define _SERVER_GAME_STATE_H_

#include "../../Network/NetworkEntity.h"
#include "../../Network/Message.h"
#include "../../Network/Session.h"

#include <map>
#include <set>

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
        void prepareForGameState();
        void notifyReadyForGame();
        void goToGame(int worldSeed);
        void goToScoreboard();
        void update( Message message );

        void registerWithAllPlayers(Networking::NetworkEntity *entity, Message *msg);
        void unregisterFromAllPlayers(Networking::NetworkEntity *entity);

    protected:
        void assignPlayerModes();

        /**
         * pointer to the singleton {ServerCommand} instance.
         */
        ServerCommand *command;

        /**
         * map of connected players.
         */
        std::map<Session*, PlayerEntity*> players;

        /**
         * number of players waiting for the game to start.
         */
        int playersWaitingToLaunch;
};

#endif
