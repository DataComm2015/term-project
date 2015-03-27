#include "NetworkControllerEntity.h"

NetworkController::NetworkController(int id)
    :NetworkEntity(id,NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER)
{
}

NetworkController::~NetworkController()
{
}

void NetworkController::onUpdate( Message message )
{
    parseEventMessage(message);
}

void NetworkController::onUnregister( Session * session, Message message )
{
    parseEventMessage(message);
}

void NetworkController::parseEventMessage(Message& message)
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
