#ifndef _NETWORK_CONTROLLER_ENTITY
#define _NETWORK_CONTROLLER_ENTITY

#include "../../Engine/Controller.h"
#include "../../Network/NetworkEntity.h"

namespace Marx
{
    class Event;
    class Controller;
}

namespace Networking
{
    class NetworkEntity;
    class Session;
    struct Message;
}

/**
 * the {ServerNetworkController} class on the server is logically mapped to a
 *   {ClientNetworkController} on the client. other controllers such as AI
 *   controllers should inherit from the {ClientNetworkController} class, and
 *   get their entity to do stuff by using the addEvent method.
 *
 * whenever the {ServerNetworkController::addEvent} function is called, it will
 *   get its entity to do stuff. if the event should be received on the client
 *   side as well, then the event should be converted into a Networking::Message
 *   in the {ServerNetworkController::sendEventMessage} method. the same message
 *   will be received in the {ClientNetworkController::onUpdate} function, where
 *   it needs to be handled, and converted from a message back into an event,
 *   then added to the {NetworkController's} event queue.
 */
class ClientNetworkController
    : public ::Marx::Controller
    , public Networking::NetworkEntity
{
public:
    ClientNetworkController(int id);
    virtual ~ClientNetworkController();
    virtual void onUpdate(Networking::Message message);
    virtual void onUnregister(Networking::Session* session,
        Networking::Message message);

private:
    void parseEventMessage(Networking::Message& message);
};

#endif
