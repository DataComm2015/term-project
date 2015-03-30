#include "NetworkControllerEntity.h"

#include <stdio.h>

using Networking::Message;
using Networking::Session;
using Networking::NetworkEntity;

NetworkControllerEntity::NetworkControllerEntity(int id)
    :NetworkEntity(id,NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER)
{
}

NetworkControllerEntity::NetworkControllerEntity(int id, int type)
    :NetworkEntity(id,type)
{
}

NetworkControllerEntity::~NetworkControllerEntity()
{
}

void NetworkControllerEntity::onUpdate( Message message )
{
    parseEventMessage(message);
}

void NetworkControllerEntity::onUnregister( Session * session, Message message )
{
    parseEventMessage(message);
}

void NetworkControllerEntity::parseEventMessage(Message& message)
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
