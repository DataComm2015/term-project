#include "ServerNetworkController.h"

#include "../NetworkEntityPairs.h"
#include "../Event.h"
#include <stdio.h>
#include <cstring>

ServerNetworkController::ServerNetworkController()
    :Controller()
    ,NetworkEntity((int)NetworkEntityPair::SERVERCONTROLLER_NETCONTROLLER)
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

void ServerNetworkController::addEvent(Event *event)
{
    sendEventMessage(event);
    Controller::addEvent(event);
}

void ServerNetworkController::sendEventMessage(Event *event)
{
    // create network message from event
    switch(event->type)
    {
        case ::Marx::MOVE:
        {
            // cast event to event subclass
            MoveEvent* me = (MoveEvent*) event;

            // parse move event into move message
            MoveMessage mm;
            mm.x      = me->getX();
            mm.y      = me->getY();
            mm.xDir   = me->getXDir();
            mm.yDir   = me->getYDir();
            mm.forced = me->forced();

            // message to be sent over the network
            Message message;
            message.data = &mm;
            message.len  = sizeof(MoveMessage);
            message.type = ::Marx::MOVE;

            printf("sending:   x: %f  y:%f xDir:%d yDir%d \n",mm.x,mm.y, mm.xDir, mm.yDir);

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
    switch((PlayerCommandMsgType)msg.type)
    {
        case PlayerCommandMsgType::START_MV_LEFT_COMMAND:
        {
            MoveEvent *event = new MoveEvent(-1,0,-1,0,0);
            printf("receiving: x: %f  y: %f\n",event->getX(),event->getY());
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::START_MV_RIGHT_COMMAND:
        {
            MoveEvent *event = new MoveEvent(1,0,1,0,0);
            printf("receiving: x: %f  y: %f\n",event->getX(),event->getY());
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::START_MV_UP_COMMAND:
        {
            MoveEvent *event = new MoveEvent(0,-1,0,-1,0);
            printf("receiving: x: %f  y: %f\n",event->getX(),event->getY());
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::START_MV_DOWN_COMMAND:
        {
            MoveEvent *event = new MoveEvent(0,1,0,1,0);
            printf("receiving: x: %f  y: %f\n",event->getX(),event->getY());
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::STOP_MV_LEFT_COMMAND:
        {
            MoveEvent *event = new MoveEvent(0,0,0,0,0);
            printf("receiving: x: %f  y: %f\n",event->getX(),event->getY());
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::STOP_MV_RIGHT_COMMAND:
        {
            MoveEvent *event = new MoveEvent(0,0,0,0,0);
            printf("receiving: x: %f  y: %f\n",event->getX(),event->getY());
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::STOP_MV_UP_COMMAND:
        {
            MoveEvent *event = new MoveEvent(0,0,0,0,0);
            printf("receiving: x: %f  y: %f\n",event->getX(),event->getY());
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::STOP_MV_DOWN_COMMAND:
        {
            MoveEvent *event = new MoveEvent(0,0,0,0,0);
            printf("receiving: x: %f  y: %f\n",event->getX(),event->getY());
            addEvent(event);
            break;
        }
    }
}
