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

            // send the network event
            update(message);
            break;
    	}
		case ::Marx::ATTACK:
		{
			// cast event to event subclass
			AttackEvent *ae = (AttackEvent*) event;

			// parse attack event into move message
			AttackMessage am;
			am.srcid 		= ae->getSrc();
			am.action	= ae->getAction();
			am.cellx	= ae->getCellX();
			am.celly	= ae->getCellY();
			
			// message to be sent over the network
			Message message;
			message.data = &am;
			message.len = sizeof(AttackMessage);
			message.type = ::Marx::ATTACK;

			// send the network event
			update(message);
			break;
		}
		case ::Marx::SK_ATTACK:
		{
			// cast event to event subclass
			SkillAttackEvent *ae = (SkillAttackEvent*) event;

			// parse attack event into move message
			SkillAttackMessage am;
			am.srcid 		= ae->getSrc();
			am.action	= ae->getAction();
			am.destx	= ae->getDestX();
			am.desty	= ae->getDestY();
			
			// message to be sent over the network
			Message message;
			message.data = &am;
			message.len = sizeof(SkillAttackMessage);
			message.type = ::Marx::SK_ATTACK;

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
	int *moveValues;
    switch((PlayerCommandMsgType)msg.type)
    {
        case PlayerCommandMsgType::START_MV_LEFT_COMMAND:
        {
			moveValues = (int*)msg.data;
            MoveEvent *event = new MoveEvent(moveValues[0], moveValues[1], moveValues[2], moveValues[3], moveValues[4]);
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::START_MV_RIGHT_COMMAND:
        {
			moveValues = (int*)msg.data;
            MoveEvent *event = new MoveEvent(moveValues[0], moveValues[1], moveValues[2], moveValues[3], moveValues[4]);
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::START_MV_UP_COMMAND:
        {
			moveValues = (int*)msg.data;
            MoveEvent *event = new MoveEvent(moveValues[0], moveValues[1], moveValues[2], moveValues[3], moveValues[4]);
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::START_MV_DOWN_COMMAND:
        {
			moveValues = (int*)msg.data;
            MoveEvent *event = new MoveEvent(moveValues[0], moveValues[1], moveValues[2], moveValues[3], moveValues[4]);
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::STOP_MV_LEFT_COMMAND:
        {
            MoveEvent *event = new MoveEvent(0,0,0,0,0);
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::STOP_MV_RIGHT_COMMAND:
        {
            MoveEvent *event = new MoveEvent(0,0,0,0,0);
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::STOP_MV_UP_COMMAND:
        {
            MoveEvent *event = new MoveEvent(0,0,0,0,0);
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::STOP_MV_DOWN_COMMAND:
        {
            MoveEvent *event = new MoveEvent(0,0,0,0,0);
            addEvent(event);
            break;
        }
		case PlayerCommandMsgType::START_ATT_COMMAND:
		{
			
			break;
		}
		case PlayerCommandMsgType::START_SK_ATT_COMMAND:
		{
			
			break;
		}
    }
}
