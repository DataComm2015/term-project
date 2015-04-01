#ifndef _SERVER_COMMAND_H_
#define _SERVER_COMMAND_H_

#include "../Network/Server.h"
#include "../Network/Session.h"
#include "../Engine/Scene.h"

class ServerGameState;
class ServerLobbyScene;
class ServerGameScene;

using Networking::Server;
using Networking::Session;
using Marx::Scene;

/**
 * the server's implementation of the server. this thing is going to need more
 *   work.
 *
 * at the moment, it is just hard coded to create a {Player}, {ProperEntity},
 *   and {ServerController}, and register the {ServerController} and {Player}
 *   instances with the client, which will cause the client to create a
 *   {NetworkController} and {Command} instances respectively.
 */
class ServerCommand : public Server
{
    public:
        ServerCommand();
        virtual void onConnect(Session* session);
        virtual void onMessage(Session* session, char* data, int len);
        virtual void onDisconnect(Session* session, int remote);
        Scene *getActiveScene();
        ServerGameState *getGameState();
        ServerGameScene *getGameScene();
        bool isGameInProgress();
        void goToLobby();
        void prepareForGameState();
        void goToGame();
        void goToScoreboard();
        
        void playerLeft(Session *session);

    private:
	    ServerLobbyScene *lobbyScene;
	    ServerGameScene *gameScene;
        Scene *activeScene;
        
        ServerGameState *gameState;
};

#endif
