#ifndef _NETWORK_CONTROLLER_ENTITY
#define _NETWORK_CONTROLLER_ENTITY

#include "../../Engine/Controller.h"
#include "../../Network/Message.h"
#include "../../Network/Session.h"
#include "../../Network/NetworkEntity.h"
#include "../NetworkEntityPairs.h"
#include "../Event.h"

using Networking::Message;
using Networking::Session;
using Networking::NetworkEntity;

/**
 * the {ServerController} class on the server is logically mapped to a
 *   {NetworkControllerEntity} on the client. other controllers such as AI controllers
 *   should inherit from the {NetworkControllerEntity} class, and get their entity to
 *   do stuff by using the addEvent method.
 *
 * whenever the {ServerController::addEvent} function is called, it will get its
 *   entity to do stuff. if the event should be received on the client side as
 *   well, then the event should be converted into a Networking::Message in the
 *   {ServerController::sendEventMessage} method. the same message will be
 *   received in the {NetworkControllerEntity::onUpdate} function, where it needs to
 *   be handled, and converted from a message back into an event, then added to
 *   the {NetworkController's} event queue.
 */
class NetworkControllerEntity : public ::Marx::Controller, public NetworkEntity
{
public:
    NetworkControllerEntity(int id);
    NetworkControllerEntity(int id, int type);
    ~NetworkControllerEntity();
    virtual void onUpdate( Message message );
    virtual void onUnregister( Session * session, Message message );
private:
    void parseEventMessage(Message& message);
};

#endif
