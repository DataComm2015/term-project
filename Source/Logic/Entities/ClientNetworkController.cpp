#include "ClientNetworkController.h"

#include "../../Engine/Event.h"

#include "../../Network/Message.h"
#include "../../Network/Session.h"

#include "../NetworkEntityPairs.h"

#include "../Event.h"

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
        case ::Marx::UPDATE:
        {
            UpdateMessage *um = (UpdateMessage*) message.data;
            UpdateEvent *ev = new UpdateEvent(um->x, um->y);
            addEvent(ev);
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
