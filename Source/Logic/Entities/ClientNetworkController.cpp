/*------------------------------------------------------------------------------
-- FILE:        ClientNetworkController.cpp
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun, Eric Tsang
--
-- INTERFACE:       ClientNetworkController(int id);
                    virtual ~ClientNetworkController();
                    virtual void onUpdate(Networking::Message message);
                    virtual void onUnregister(Networking::Session* session, Networking::Message message);
                    void parseEventMessage(Networking::Message& message);

-- RETURNS:         void
--
-- NOTES:           the {ServerNetworkController} class on the server is logically mapped to a
                    {ClientNetworkController} on the client. other controllers such as AI
                    controllers should inherit from the {ClientNetworkController} class, and
                    get their entity to do stuff by using the addEvent method.
------------------------------------------------------------------------------*/

#include "ClientNetworkController.h"

#include "../../Engine/Event.h"

#include "../../Network/Message.h"
#include "../../Network/Session.h"

#include "../NetworkEntityPairs.h"

#include "../Event.h"
#include "../Skills.h"

#include <stdio.h>

using ::Marx::Event;
using Marx::Controller;
using Networking::Message;
using Networking::Session;
using Networking::NetworkEntity;

ClientNetworkController::ClientNetworkController(int id)
    : Controller()
    , NetworkEntity(id,(int)NetworkEntityPair::SERVERCONTROLLER_NETCONTROLLER)
{
}

ClientNetworkController::~ClientNetworkController()
{
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ClientNetworkController::onUpdate
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void ClientNetworkController::onUpdate( Message message )
--                  message: message received over the network

-- RETURNS:         void
--
-- NOTES:           parses the message and where it is added to the eventQueue
------------------------------------------------------------------------------*/
void ClientNetworkController::onUpdate( Message message )
{
    parseEventMessage(message);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ClientNetworkController::onUnregister
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void ClientNetworkController::onUnregister( Session * session, Message message )
            session - session to unregister
            message - message sent with unregister

-- RETURNS:         void
--
-- NOTES:           unregisters session and handles message
------------------------------------------------------------------------------*/
void ClientNetworkController::onUnregister( Session * session, Message message )
{
    parseEventMessage(message);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ClientNetworkController::parseEventMessage
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun, Eric Tsang
--
-- INTERFACE:       void ClientNetworkController::parseEventMessage( Message& message )
            message - reference to the message

-- RETURNS:         void
--
-- NOTES:           convinience method to handle messages
------------------------------------------------------------------------------*/
void ClientNetworkController::parseEventMessage( Message& message )
{
    switch(message.type)
    {
		case ::Marx::MOVE:
		{
		    // case message payload
		    MoveMessage* mm = (MoveMessage*) message.data;

		    // create event from message data
		    MoveEvent *ev = new MoveEvent(mm->x, mm->y, mm->xDir, mm->yDir, mm->forced);

		    // add event to event queue
		    addEvent(ev);
		    break;
		}
		case ::Marx::ATTACK:
		{
			// case message payload
			AttackMessage* mm = (AttackMessage*) message.data;

			// create event from message data
			AttackEvent *ev = new AttackEvent(mm->srcid, mm->action, mm->cellx, mm->celly);

			// add event to event queue
			addEvent(ev);
			break;
		}
		case ::Marx::SK_ATTACK:
		{
			// case message payload
			SkillAttackMessage* mm = (SkillAttackMessage*) message.data;

			// create event from message data
			SkillAttackEvent *ev = new SkillAttackEvent(mm->srcid, mm->action, mm->destx, mm->desty);

			// add event to event queue
			addEvent(ev);
			break;
		}
		case ::Marx::SET_HEALTH:
		{
			// case message payload
			SetHealthMessage* mm = (SetHealthMessage*) message.data;

			// create event from message data
			SetHealthEvent *ev = new SetHealthEvent(mm->entid, mm->typeHeal, mm->change);

			// add event to event queue
			addEvent(ev);
			break;
		}
        case ::Marx::UPDATE:
        {
            UpdateMessage *um = (UpdateMessage*) message.data;
            UpdateEvent *ev = new UpdateEvent(um->x, um->y);
            addEvent(ev);
        }
        case ::Marx::SKILL:
        {
            // turn network message back into skill event, and call addEvent()
            skill* sk = ((skill*)message.data);
            
            SkillEvent *ev = new SkillEvent(sk->curX, sk->curY, sk->radius, sk->val, sk->st);
            
            addEvent(ev);
            break;
        }
		case ::Marx::ADD_POINTS:
		{
			AddPointsMessage *pm = (AddPointsMessage*) message.data;
			AddPointsEvent *ev = new AddPointsEvent(pm->points);

			addEvent(ev);
			break;
		}
        default:
        {
            printf("WARNING: ClientNetworkController::parseEventMessage received an "
                "unknown event type. please add new case to switch statement");
            fflush(stdout);
            break;
        }
    }
}
