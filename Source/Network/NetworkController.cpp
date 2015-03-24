/*

Not finished yet, barebones implementation

*/
#include "NetworkController.h"

#include "Message.h"
#include "Session.h"
#include "NetworkEntityMultiplexer.h"
#include "../Engine/MoveEvent.h"

namespace Networking
{

    using ::Marx::ATTACK;
    using ::Marx::MOVE;
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
	void Networking::NetworkController::onUpdate( Message message )
	{
		parseMessage(message);
	}


	/*------------------------------------------------------------------------------
	-- FUNCTION:        NetworkController::onRegister
	--
	-- DATE:            March 17, 2015
	--
	-- REVISIONS:       (Date and Description)
	--
	-- DESIGNER:        Jeff Bayntun
	--
	-- PROGRAMMER:      Jeff Bayntun
	--
	-- INTERFACE:       void NetworkController::onRegister( int type, Session * session, Message message )
	--                  type  -  type of this network entity
			    session - session to register
			    message - message sent with register

	-- RETURNS:         void
	--
	-- NOTES:           registers session and handles message
	----------------------------------------------------------------------------------*/
	void Networking::NetworkController::onRegister( int type, Session * session, Message message )
	{	
		NetworkEntity::silentRegister(session);
		parseMessage(message);
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
	void Networking::NetworkController::onUnregister( Session * session, Message message )
	{
		NetworkEntity::silentUnregister(session);
		parseMessage(message);
	}
	/*------------------------------------------------------------------------------
	-- FUNCTION:        NetworkController::parseMessage
	--
	-- DATE:            March 17, 2015
	--
	-- REVISIONS:       (Date and Description)
	--
	-- DESIGNER:        Jeff Bayntun
	--
	-- PROGRAMMER:      Jeff Bayntun
	--
	-- INTERFACE:       void NetworkController::parseMessage( Message& message )
			    message - reference to the message

	-- RETURNS:         void
	--
	-- NOTES:           convinience method to handle messages
	---------------------------------------------------------------------------------*/
	void Networking::NetworkController::parseMessage( Message& message )
	{
        // probably need a better way of figuring out the type, wont
        // know it's a move message here...
        MoveMessage* mm;
        mm = (MoveMessage*) message.data;

        switch(mm->type)
		{
        case MOVE:
            addMoveEvent(mm->x, mm->y, mm->forced);
			break;
        case ATTACK:
            //attack stuff
            break;
		default:
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
    void Networking::NetworkController::sendMoveUpdate(float x, float y, bool forced)
    {
        MoveMessage mm;
        mm.x = x;
        mm.y = y;
        mm.forced = forced;
        mm.type = MOVE;

        Message message;
        message.data = &mm;
        message.len = sizeof(mm);
        message.type = EVENT;

        update(message);
    }

}



