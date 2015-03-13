#include "NetworkEntity.h"
#include "NetworkEntityMultiplexer.h"
#include "Message.h"

using namespace std;

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        NetworkEntity::NetworkEntity
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       NetworkEntity::NetworkEntity( NetworkEntityMultiplexer * mux, int id, int type )
--                  id: the id of this network entity
                    type: they type of this network entity
                    mux: the multiplexer for this network entity

-- RETURNS:         void
--
-- NOTES:           Creates a NetworkEntity object
-----------------------------------------------------------------------------------------------*/
Networking::NetworkEntity::NetworkEntity( int id, int type )
{
    this->id = id;
    this->type = type;
    this->mux = NetworkEntityMultiplexer::getInstance();
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        NetworkEntity::update
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       NetworkEntity::update( Message message  )
--                  message: message to send

-- RETURNS:         -1 on failure
--
-- NOTES:           a message to send across the network, will call on update on receiving
                    side.
-----------------------------------------------------------------------------------------------*/
int Networking::NetworkEntity::update( Message message )
{
    return mux->update(id, registeredSessions, message);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        NetworkEntity::onUpdate
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:      Eric Tsang
--
-- INTERFACE:       NetworkEntity::onUpdate( Message message )
--                  message: message sent from the other side
--
-- RETURNS:         void
--
-- NOTES:           Meant to be overwritten by user to handle an incoming update
-----------------------------------------------------------------------------------------------*/
void Networking::NetworkEntity::onUpdate( Message message )
{
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        NetworkEntity::register
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       NetworkEntity::register( Session * session, Message message )
--                  session: session to register
--                  message: message to send
--
-- RETURNS:         -1 on failure
--
-- NOTES:           registers a session so the NetworkEntity can send and recieve
                    to and from the session.
-----------------------------------------------------------------------------------------------*/
int Networking::NetworkEntity::registerSession( Session * session, Message message )
{
    registeredSessions.insert(session);
    return mux->registerSession(id, type, session, message);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        NetworkEntity::onRegister
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:      Eric Tsang
--
-- INTERFACE:       NetworkEntity::onRegister( Session * session, Message message )
--                  session: session that has been registered to the entity
--                  message: message that sent from the other side
--
-- RETURNS:         void
--
-- NOTES:           Meant to be overwritten by user. Called when the associated entity on
--                  the other side calls the register method. MUST CALL silentRegister();
-----------------------------------------------------------------------------------------------*/
void Networking::NetworkEntity::onRegister( int type, Session * session, Message message )
{
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        NetworkEntity::unregister
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       NetworkEntity::unregister( Session * session, Message message )
--                  session: session to unregister
--                  message: message to send to that session
--
-- RETURNS:         -1 on failure
--
-- NOTES:           unregisters this session from this entity
-----------------------------------------------------------------------------------------------*/
int Networking::NetworkEntity::unregisterSession( Session * session, Message message )
{
    if( registeredSessions.erase(session) == 0 ) // not in set
    {
        return -1;
    }
    return mux->unregisterSession(id, session, message);
}

/**
 *
 */
/*----------------------------------------------------------------------------------------------
-- FUNCTION:        NetworkEntity::onUnregister
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:      Eric Tsang
--
-- INTERFACE:       NetworkEntity::onUnregister( Session * session, Message message );
--                  session: session that has been unregistered from the entity
--                  message: message that sent from the other side
--
-- RETURNS:         void
--
-- NOTES:           Meant to be overwritten by the user. Called when the associated
--                  entity on the other side calls the unregister method.
--                  MUST CALL silentUnregister();
-----------------------------------------------------------------------------------------------*/
void Networking::NetworkEntity::onUnregister( Session * session, Message message )
{
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        NetworkEntity::silentRegister
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       NetworkEntity::silentRegister( Session * session, Message message )
--                  session: session to register
--
-- RETURNS:         -1 on failure
--
-- NOTES:           registers this session from this entity
-----------------------------------------------------------------------------------------------*/
void Networking::NetworkEntity::silentRegister( Session* session )
{
    registeredSessions.insert(session);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        NetworkEntity::silentUnregister
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       NetworkEntity::silentUnregister( Session * session, Message message )
--                  session: session to unregister
--
-- RETURNS:         -1 on failure
--
-- NOTES:           unregisters this session from this entity
-----------------------------------------------------------------------------------------------*/
void Networking::NetworkEntity::silentUnregister( Session* session )
{
    registeredSessions.erase(session);
}

