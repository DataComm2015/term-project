#ifndef _COMMAND_ENTITY_H_
#define _COMMAND_ENTITY_H_

#include "../KeyListener.h"
#include "../ClickListener.h"
#include "../../Network/Message.h"
#include "../../Network/Session.h"
#include "../../Network/NetworkEntity.h"
#include "../Event.h"

class ClientMux;

#include "PlayerEntity.h"
#include "../ClientLobbyScene.h"

using Networking::NetworkEntity;
using Networking::Message;
using Networking::Session;

class GameScene;
struct PlayerLobbyChoices;

/**
 * the {Player} is resides the server, and is logically mapped to the {Command}
 *   class over the network, which is on the client side.
 *
 * the client sends command using {Command::update} such as move commands or
 *   others like choosing their character to the Server. such commands are
 *   handled in the {Player::onUpdate} method. and sent using the. .
 */
class CommandEntity : public NetworkEntity, public KeyListener, public ClickListener
{
    public:
        CommandEntity(int id, GameScene *gameScene, ClientMux* client);
        ~CommandEntity();

        PLAYER_MODE getPlayerMode();
        void notifyServerLobbySelections(PlayerLobbyChoices *selections);

    protected:
        virtual void onKeyPressed(int key);
        virtual void onKeyReleased(int key);
	virtual void onMouseClick(int key, int srcid, enum ActionType action, float xpos, float ypos);
        virtual void onRegister(Session *session);
        virtual void onUnregister(Session* session, Message message);
        virtual void onUpdate(Message message);

    private:
        ClientMux* clientmux;
        GameScene* _gameScene;
        PLAYER_MODE playerMode;
};

#endif

