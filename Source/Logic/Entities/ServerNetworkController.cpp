#include "ServerNetworkController.h"

#include "../NetworkEntityPairs.h"
#include "../Event.h"
#include <stdio.h>

ServerNetworkController::ServerNetworkController()
    :NetworkEntity(NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER)
{
}

ServerNetworkController::ServerNetworkController(int type)
    :NetworkEntity(type)
{
    printf("TYPE: %d, ID: %d\r\n", type, id);
}

ServerNetworkController::~ServerNetworkController()
{
}

void ServerNetworkController::addEvent(Event event)
{
    Controller::addEvent(event);
    sendEventMessage(event);
}

void ServerNetworkController::sendEventMessage(Event event)
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
        printf("\r\nWARNING: NetworkController::sendEventMessage received an "
            "unknown event type. please add new case to switch statement\r\n");
        fflush(stdout);
        break;
    }
}

void ServerNetworkController::onUnregister(Session* session, Message message)
{
}

void ServerNetworkController::onUpdate(Message msg)
{
}
