/*

Not finished yet, barebones implementation

*/
#include "NetworkController.h"

#include "Message.h"
#include "Session.h"
#include "NetworkEntityMultiplexer.h"
#include "../Engine/MoveEvent.h"

using namespace Networking;
using ::Marx::MoveMessage;

/*------------------------------------------------------------------------------
-- FUNCTION:        NetworkController::onUpdate
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void NetworkController::onUpdate( Message message )
--                  message: message received over the network

-- RETURNS:         void
--
-- NOTES:           parses the message and where it is added to the eventQueue
----------------------------------------------------------------------------------*/
void NetworkController::onUpdate( Message message )
{
    parseEventMessage(message);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        NetworkController::onUnregister
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void NetworkController::onUnregister( Session * session, Message message )
            session - session to unregister
            message - message sent with unregister

-- RETURNS:         void
--
-- NOTES:           unregisters session and handles message
----------------------------------------------------------------------------------*/
void NetworkController::onUnregister( Session * session, Message message )
{
    parseEventMessage(message);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        NetworkController::parseEventMessage
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void NetworkController::parseEventMessage( Message& message )
            message - reference to the message

-- RETURNS:         void
--
-- NOTES:           convinience method to handle messages
---------------------------------------------------------------------------------*/
void NetworkController::parseEventMessage( Message& message )
{
    switch(message.type)
    {
    case ::Marx::MOVE:
        // case message payload
        MoveMessage* mm = (MoveMessage*) message.data;

        // create event from message data
        MoveEvent ev(mm->x, mm->y, mm->forced);

        // add event to event queue
        addEvent(ev);
        break;
    default:
        printf("WARNING: NetworkController::parseEventMessage received an "
            "unknown event type. please add new case to switch statement");
        fflush(stdout);
        break;
    }
}

/*------------------------------------------------------------------------------
-- FUNCTION:        NetworkController::sendMoveUpdate
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void NetworkController::sendMoveUpdate(float x, float y, bool forced)
--                  x: x position moved to
                    y: y position moved to
                    forced: if move is forced

-- RETURNS:         void
--
-- NOTES:           prepares message to be sent across the network
----------------------------------------------------------------------------------*/
void NetworkController::sendEventMessage(Event ev)
{

    // create network message from event
    switch(ev.type)
    {
    case ::Marx::MOVE
        // cast event to event subclass
        MoveEvent* me = (MoveEvent*) &ev;

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
    default:
        printf("WARNING: NetworkController::sendEventMessage received an "
            "unknown event type. please add new case to switch statement");
        fflush(stdout);
        break;
    }
}
