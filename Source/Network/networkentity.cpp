#include "NetworkEntity.h"
#include "NetworkEntityMultiplexer.h"

using namespace std;

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		NetworkEntity::NetworkEntity
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Networking Teams
--
-- PROGRAMMER:		Jeff Bayntun
--
-- INTERFACE:		NetworkEntity::NetworkEntity( NetworkEntityMultiplexer * mux, int id, int type )
--                  id: the id of this network entity
                    type: they type of this network entity
                    mux: the multiplexer for this network entity

-- RETURNS: 		void
--
-- NOTES:			Creates a NetworkEntity object
-----------------------------------------------------------------------------------------------*/
Networking::NetworkEntity::NetworkEntity( NetworkEntityMultiplexer * mux, int id, int type )
{
    this->id = id;
    this->type = type;
    this->mux = mux;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		NetworkEntity::update
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Networking Teams
--
-- PROGRAMMER:		Jeff Bayntun
--
-- INTERFACE:		NetworkEntity::update( Message message  )
--                  message: message to send

-- RETURNS: 		-1 on failure
--
-- NOTES:			a message to send across the network, will call on update on receiving
                    side.
-----------------------------------------------------------------------------------------------*/
int Networking::NetworkEntity::update( Message message )
{
    return mux->update(id, registeredSessions, message);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		NetworkEntity::register
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Networking Teams
--
-- PROGRAMMER:		Jeff Bayntun
--
-- INTERFACE:		NetworkEntity::register( Session * session, Message message )
--                  session: session to register
--                  message: message to send
--
-- RETURNS: 		-1 on failure
--
-- NOTES:			registers a session so the NetworkEntity can send and recieve
                    to and from the session.
-----------------------------------------------------------------------------------------------*/
int Networking::NetworkEntity::registerSession( Session * session, Message message )
{
    registeredSessions.insert(session);
    return mux->registerSession(session, message);
}


/*----------------------------------------------------------------------------------------------
-- FUNCTION:		NetworkEntity::unregister
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Networking Teams
--
-- PROGRAMMER:		Jeff Bayntun
--
-- INTERFACE:		NetworkEntity::unregister( Session * session, Message message )
--                  session: session to unregister
--                  message: message to send to that session
--
-- RETURNS: 		-1 on failure
--
-- NOTES:			unregisters this session from this entity
-----------------------------------------------------------------------------------------------*/
int Networking::NetworkEntity::unregister( Session * session, Message message )
{
    if( registeredSessions.erase(session) == 0 ) // not in set
    {
        return -1;
    }
    return mux->unregisterSession(session, message);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		NetworkEntity::silentRegister
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Networking Teams
--
-- PROGRAMMER:		Jeff Bayntun
--
-- INTERFACE:		NetworkEntity::silentRegister( Session * session, Message message )
--                  session: session to register
--
-- RETURNS: 		-1 on failure
--
-- NOTES:			registers this session from this entity
-----------------------------------------------------------------------------------------------*/
void Networking::NetworkEntity::silentRegister( Session session )
{
    registeredSessions.insert(session);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:		NetworkEntity::silentUnregister
--
-- DATE:			February 27, 2015
--
-- REVISIONS:		(Date and Description)
--
-- DESIGNER:		Networking Teams
--
-- PROGRAMMER:		Jeff Bayntun
--
-- INTERFACE:		NetworkEntity::silentUnregister( Session * session, Message message )
--                  session: session to unregister
--
-- RETURNS: 		-1 on failure
--
-- NOTES:			unregisters this session from this entity
-----------------------------------------------------------------------------------------------*/
void Networking::NetworkEntity::silentRegister( Session session )
{
    registeredSessions.erase(session);
}

