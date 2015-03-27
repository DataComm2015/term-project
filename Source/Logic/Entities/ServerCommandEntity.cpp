#include "ServerCommandEntity.h"

#include "../NetworkEntityPairs.h"
#include "../Event.h"
#include <stdio.h>

ServerCommandEntity::ServerCommandEntity()
    :NetworkEntity(NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER)
{
}

ServerCommandEntity::~ServerCommandEntity()
{
}

void ServerCommandEntity::addEvent(Event event)
{
    Controller::addEvent(event);
    sendEventMessage(event);
}

void ServerCommandEntity::sendEventMessage(Event event)
{
    // create network message from event
    switch(event.type)
    {
    case ::Marx::MOVE:
    {
        // cast event to event subclass
        MoveEvent* me = (MoveEvent*) &event;

        // parse move event into move message
        MoveMessage mm;
        mm.x      = me->getX();
        mm.y      = me->getY();
        mm.forced = me->forced();

        // message to be sent over the network
        Message message;
        message.data = &mm;
        message.len  = sizeof(mm);
        message.type = ::Marx::MOVE;

        // send the network event
        update(message);
        break;
    }
    default:
        printf("WARNING: NetworkController::sendEventMessage received an "
            "unknown event type. please add new case to switch statement");
        fflush(stdout);
        break;
    }
}

void ServerCommandEntity::onUnregister(Session* session, Message message)
{
}

void ServerCommandEntity::onUpdate(Message msg)
{
}
