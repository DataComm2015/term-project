#ifndef _NETWORK_CONTROLLER_ENTITY
#define _NETWORK_CONTROLLER_ENTITY

#include "../../Engine/Controller.h"
#include "../../Network/Message.h"
#include "../../Network/NetworkEntity.h"

/**
 * the {ServerController} class on the server is logically mapped to a
 *   {NetworkController} on the client. other controllers such as AI controllers
 *   should inherit from the {ServerController} class, and get their entity to
 *   do stuff by using the addEvent method.
 *
 * whenever the {ServerController::addEvent} function is called, it will get its
 *   entity to do stuff. if the event should be received on the client side as
 *   well, then the event should be converted into a Networking::Message in the
 *   {ServerController::sendEventMessage} method. the same message will be
 *   received in the {NetworkController::onUpdate} function, where it needs to
 *   be handled, and converted from a message back into an event, then added to
 *   the {NetworkController's} event queue.
 */
class NetworkController : public ::Marx::Controller, public NetworkEntity
{
public:
    NetworkController(int id)
        :NetworkEntity(id,NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER)
    {
    }
    ~NetworkController()
    {
    }
    virtual void onUpdate( Message message )
    {
        parseEventMessage(message);
    }
    virtual void onUnregister( Session * session, Message message )
    {
        parseEventMessage(message);
    }
private:
    void parseEventMessage(Message& message)
    {
        switch(message.type)
        {
        case ::Marx::MOVE:
        {
            // case message payload
            MoveMessage* mm = (MoveMessage*) message.data;

            // create event from message data
            MoveEvent ev(mm->x, mm->y, mm->forced);

            // add event to event queue
            addEvent(ev);
            break;
        }
        default:
            printf("WARNING: NetworkController::parseEventMessage received an "
                "unknown event type. please add new case to switch statement");
            fflush(stdout);
            break;
        }
    }
};

#endif
