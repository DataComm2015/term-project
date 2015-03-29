#ifndef _CLIENT_MUX_H_
#define _CLIENT_MUX_H_

#include "../../Network/Session.h"
#include "../../Network/Message.h"
#include "../../Network/NetworkEntityMultiplexer.h"

using Networking::Session;
using Networking::Message;
using Networking::NetworkEntity;
using Networking::NetworkEntityMultiplexer;

class GameScene;
class ClientLobbyScene;
class ClientGameState;
class CommandEntity;

/**
 * the client's implementation of the {NetworkEntityMultiplexer}. this thing is
 *   going to need more work.
 *
 * when the server registers the {ServerController} and {Player} instances with
 *   the client, {Mux::onRegister} will be triggered which. it should create a
 *   {NetworkController} and {Command} instances respectively.
 */
class ClientMux : public Networking::NetworkEntityMultiplexer
{
    public:
        ClientMux(GameScene* scene, ClientLobbyScene* lobbyScene);
        virtual ~ClientMux();
        virtual NetworkEntity* onRegister(int id, int entityType,
            Session* session, Message msg);
            
        void shutdown();
    private:
        Session *session;
        GameScene* _gameScene;
        ClientLobbyScene* _lobbyScene;
        CommandEntity *command;
        ClientGameState *gameState;
};

#endif
