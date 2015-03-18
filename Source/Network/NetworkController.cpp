/*

Not finished yet, barebones implementation

*/
#include "NetworkController.h"

#include "Message.h"
#include "Session.h"
#include "NetworkEntityMultiplexer.h"
#include "../Engine/Event.h"

namespace Networking
{

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
		switch(message.type)
		{
		case 1:
			//neet to translate the message into an event.. however that will work
			eventQueue.push_back(new Event());
			break;
		default:
			break;
		}	
		
	}

}



