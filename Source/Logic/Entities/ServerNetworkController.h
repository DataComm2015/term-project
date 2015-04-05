#ifndef SERVER_COMMAND_ENTITY_H_
#define SERVER_COMMAND_ENTITY_H_

#include "../../Engine/Controller.h"
#include "../../Network/Session.h"
#include "../../Network/Message.h"
#include "../../Network/NetworkEntity.h"
#include "../../Engine/Event.h"

using Networking::NetworkEntity;
using Networking::Session;
using Networking::Message;
using Marx::Controller;
using Marx::Event;

/**
 * the {ServerNetworkController} class on the server is logically mapped to a
 *   {ClientNetworkController} on the client. other controllers such as AI
 *   controllers should inherit from the {ServerNetworkController} class, and
 *   get their entity to do stuff by using the addEvent method.
 *
 * whenever the {ServerNetworkController::addEvent} function is called, it will
 *   get its entity to do stuff. if the event should be received on the client
 *   side as well, then the event should be converted into a Networking::Message
 *   in the {ServerController::sendEventMessage} method. the same message will
 *   be received in the {ClientNetworkController::onUpdate} function, where it
 *   needs to be handled, and converted from a message back into an event, then
 *   added to the {ClientNetworkController's} event queue.
 */
class ServerNetworkController : public Controller, public Networking::NetworkEntity
{
    public:
        ServerNetworkController();
        virtual ~ServerNetworkController();
        virtual void addEvent(Event *event);
        virtual void onUpdate(Message msg);
        void sendEventMessage(Event *event);

    protected:
        ServerNetworkController(int type);
};

#endif
