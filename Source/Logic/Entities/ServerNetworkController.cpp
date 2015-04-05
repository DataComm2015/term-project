#include "ServerNetworkController.h"

#include "../NetworkEntityPairs.h"
#include "../Event.h"
#include <stdio.h>
#include <cstring>

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerNetworkController::ServerNetworkController
--
-- DATE:            April 1, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Eric Tsang
--
-- PROGRAMMER:      Calvin Rempel, Eric Tsang
--
-- INTERFACE:       ServerNetworkController::ServerNetworkController()
--
-- RETURNS:         void
--
-- NOTES:           constructor for the {ServerGameState} class.
------------------------------------------------------------------------------*/
ServerNetworkController::ServerNetworkController()
    :Controller()
    ,NetworkEntity((int)NetworkEntityPair::SERVERCONTROLLER_NETCONTROLLER)
{
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerNetworkController::ServerNetworkController
--
-- DATE:            April 1, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Eric Tsang
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       ServerNetworkController::ServerNetworkController(int type)
--                  type - the
--
-- RETURNS:         void
--
-- NOTES:           destructor for the {ServerGameState} class.
------------------------------------------------------------------------------*/
ServerNetworkController::ServerNetworkController(int type)
    :NetworkEntity(type)
{
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerNetworkController::~ServerNetworkController
--
-- DATE:            April 1, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Eric Tsang
--
-- PROGRAMMER:      Calvin Rempel, Eric Tsang
--
-- INTERFACE:       ServerNetworkController::~ServerNetworkController()
--
-- RETURNS:         void
--
-- NOTES:           constructor for the {ServerGameState} class.
------------------------------------------------------------------------------*/
ServerNetworkController::~ServerNetworkController()
{
}

/*------------------------------------------------------------------------------
-- FUNCTION:        void ServerNetworkController::addEvent
--
-- DATE:            April 1, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Eric Tsang
--
-- PROGRAMMER:      Calvin Rempel, Eric Tsang
--
-- INTERFACE:       void ServerNetworkController::addEvent(Event *event)
--
-- RETURNS:         void
--
-- NOTES:           adds an even into the event queue, but since this is the
--                  server side, it will send the event to the clients first,
--                  so that they can enqueue it into their own event queue, and
--                  then the server enqueues the event into its event queue.
------------------------------------------------------------------------------*/
void ServerNetworkController::addEvent(Event *event)
{
    sendEventMessage(event);
    Controller::addEvent(event);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        void ServerNetworkController::sendEventMessage
--
-- DATE:            April 1, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Eric Tsang
--
-- PROGRAMMER:      Calvin Rempel, Eric Tsang
--
-- INTERFACE:       void ServerNetworkController::sendEventMessage(Event *event)
--
-- RETURNS:         void
--
-- NOTES:           converts an event into a message that can be sent over the
--                  network.
------------------------------------------------------------------------------*/
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
			am.srcid 	= ae->getSrc();
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
			am.srcid 	= ae->getSrc();
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
        case ::Marx::SET_HEALTH:
		{
			// cast event to event subclass
			SetHealthEvent *sh = (SetHealthEvent*) event;

			// parse attack event into move message
			SetHealthMessage sm;
			sm.entid 	= sh->getEntity();
			sm.change	= sh->getChange();
			
			// message to be sent over the network
			Message message;
			message.data = &sm;
			message.len = sizeof(SetHealthMessage);
			message.type = ::Marx::SET_HEALTH;

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

/*------------------------------------------------------------------------------
-- FUNCTION:        void ServerNetworkController::onUpdate
--
-- DATE:            April 1, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Eric Tsang
--
-- PROGRAMMER:      Calvin Rempel, Eric Tsang
--
-- INTERFACE:       void ServerNetworkController::onUpdate(Message msg)
--                  msg - message received from the update
--
-- RETURNS:         void
--
-- NOTES:           parses the message received in the update, creates the Event
--                  equivalent, and enqueues it into its event queue.
------------------------------------------------------------------------------*/
void ServerNetworkController::onUpdate(Message msg)
{
	int *moveValues;
    switch((PlayerCommandMsgType)msg.type)
    {
        case PlayerCommandMsgType::START_MV_LEFT_COMMAND:
        {
			MoveEvent *event = new MoveEvent(-1,0,-1,0,0);
			addEvent(event);
			break;
        }
        case PlayerCommandMsgType::START_MV_RIGHT_COMMAND:
        {
			MoveEvent *event = new MoveEvent(1,0,1,0,0);
			addEvent(event);
			break;
        }
        case PlayerCommandMsgType::START_MV_UP_COMMAND:
        {
			MoveEvent *event = new MoveEvent(0,-1,0,-1,0);
			addEvent(event);
			break;
        }
        case PlayerCommandMsgType::START_MV_DOWN_COMMAND:
        {
			MoveEvent *event = new MoveEvent(0,1,0,1,0);
			addEvent(event);
			break;
        }
        case PlayerCommandMsgType::STOP_MV_LEFT_COMMAND:
        {
            MoveEvent *event = new MoveEvent(1,0,1,0,0);
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::STOP_MV_RIGHT_COMMAND:
        {
            MoveEvent *event = new MoveEvent(-1,0,-1,0,0);
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::STOP_MV_UP_COMMAND:
        {
            MoveEvent *event = new MoveEvent(0,1,0,1,0);
            addEvent(event);
            break;
        }
        case PlayerCommandMsgType::STOP_MV_DOWN_COMMAND:
        {
            MoveEvent *event = new MoveEvent(0,-1,0,-1,0);
            addEvent(event);
            break;
        }
		case PlayerCommandMsgType::START_ATT_COMMAND:
		{
            printf("Starting attack");
			AttackMessage *mesg = (AttackMessage*) msg.data;
			AttackEvent *aevent = new AttackEvent(mesg->srcid, mesg->action, mesg->cellx, mesg->celly);
			addEvent(aevent);
			break;
		}
		case PlayerCommandMsgType::START_SK_ATT_COMMAND:
		{
            printf("Starting attack");
			SkillAttackMessage *smesg = (SkillAttackMessage*) msg.data;
			SkillAttackEvent *saevent = new SkillAttackEvent(smesg->srcid, smesg->action, smesg->destx, smesg->desty);
			addEvent(saevent);
			break;
		}
        default:
        	printf("\r\nWARNING: NetworkController::sendEventMessage received an "
            	"unknown event type. please add new case to switch statement\r\n");
        	fflush(stdout);
        	break;
    }
}
