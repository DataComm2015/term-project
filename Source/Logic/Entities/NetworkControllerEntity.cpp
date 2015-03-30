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

/*------------------------------------------------------------------------------
-- FUNCTION:        NetworkControllerEntity::onUpdate
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void NetworkControllerEntity::onUpdate( Message message )
--                  message: message received over the network

-- RETURNS:         void
--
-- NOTES:           parses the message and where it is added to the eventQueue
----------------------------------------------------------------------------------*/
void NetworkControllerEntity::onUpdate( Message message )
{
    parseEventMessage(message);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        NetworkControllerEntity::onUnregister
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void NetworkControllerEntity::onUnregister( Session * session, Message message )
            session - session to unregister
            message - message sent with unregister

-- RETURNS:         void
--
-- NOTES:           unregisters session and handles message
----------------------------------------------------------------------------------*/
void NetworkControllerEntity::onUnregister( Session * session, Message message )
{
    parseEventMessage(message);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        NetworkControllerEntity::parseEventMessage
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun, Eric Tsang
--
-- INTERFACE:       void NetworkControllerEntity::parseEventMessage( Message& message )
            message - reference to the message

-- RETURNS:         void
--
-- NOTES:           convinience method to handle messages
---------------------------------------------------------------------------------*/
void NetworkControllerEntity::parseEventMessage( Message& message )
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
        printf("WARNING: NetworkControllerEntity::parseEventMessage received an "
            "unknown event type. please add new case to switch statement");
        fflush(stdout);
        break;
    }
    }
}
