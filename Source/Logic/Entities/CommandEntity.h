#ifndef _COMMAND_ENTITY_H_
#define _COMMAND_ENTITY_H_

#include "Logic/KeyListener.h"
#include "Network/Message.h"
#include "Network/NetworkEntity.h"

using Networking::NetworkEntityMultiplexer;
using Networking::NetworkEntity;
using Networking::Message;
using Networking::Session;
using Networking::Client;

class GameScene;

/**
 * the {Player} is resides the server, and is logically mapped to the {Command}
 *   class over the network, which is on the client side.
 *
 * the client sends command using {Command::update} such as move commands or
 *   others like choosing their character to the Server. such commands are
 *   handled in the {Player::onUpdate} method. and sent using the. .
 */
class CommandEntity : public NetworkEntity, public KeyListener
{
    public:
        Command(int id, GameScene *scene);
        ~Command();
        
    protected:
        virtual void onKeyPressed(int key);
        virtual void onKeyReleased(int key);
        virtual void onUnregister(Session* session, Message message);
        virtual void onUpdate(Message message);
        
    private:
        GameScene *scene;
};

#endif
