#ifndef _CLIENTGAMESTATE_H_
#define _CLIENTGAMESTATE_H_

#include "../KeyListener.h"
#include "../../Network/Message.h"
#include "../../Network/Session.h"
#include "../../Network/NetworkEntity.h"

using Networking::NetworkEntity;
using Networking::Message;
using Networking::Session;

class GameScene;
class ClientLobbyScene;
class ClientScoreboardScene;
class CommandEntity;

/**
 * the {Player} is resides the server, and is logically mapped to the {Command}
 *   class over the network, which is on the client side.
 *
 * the client sends command using {Command::update} such as move commands or
 *   others like choosing their character to the Server. such commands are
 *   handled in the {Player::onUpdate} method. and sent using the. .
 */
class ClientGameState : public NetworkEntity
{
    public:
        ClientGameState(int id, CommandEntity *command, GameScene *scene, ClientLobbyScene* lobbyScene, ClientScoreboardScene* scoreScene);
        ~ClientGameState();

    protected:
        virtual void onUnregister(Session* session, Message message);
        virtual void onUpdate(Message message);

    private:
        ClientScoreboardScene* _scoreScene;
        GameScene* _gameScene;
        ClientLobbyScene* _lobbyScene;
        CommandEntity *command;
};

#endif

