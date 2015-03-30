#include "ClientNetworkController.h"

#include <stdio.h>

using Networking::Message;
using Networking::Session;
using Networking::NetworkEntity;

ClientNetworkController::ClientNetworkController(int id)
    :NetworkEntity(id,(int)NetworkEntityPair::SERVERCONTROLLER_NETCONTROLLER)
{
}

ClientNetworkController::ClientNetworkController(int id, int type)
    :NetworkEntity(id,type)
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
----------------------------------------------------------------------------------*/
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
----------------------------------------------------------------------------------*/
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
---------------------------------------------------------------------------------*/
void ClientNetworkController::parseEventMessage( Message& message )
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
    {
        printf("WARNING: ClientNetworkController::parseEventMessage received an "
            "unknown event type. please add new case to switch statement");
        fflush(stdout);
        break;
    }
    }
}
