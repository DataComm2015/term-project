#include "NetworkEntity.h"
#include "Session.h"
#include "NetworkEntityMultiplexer.h"
#include "Message.h"

#include <string.h>

#define DEBUG

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

    // add this entity to the multiplexer
    mux->entities[id] = this;
}

Networking::NetworkEntity::~NetworkEntity()
{
    // unregister all sessions registered in this entity from this entity
    Message msg;
    msg.type = MSG_TYPE_WARNING;
    for(auto session = registeredSessions.begin();
        session != registeredSessions.end(); ++session)
    {
        char output[500];

        sprintf(output,"WARNING: NetworkEntity@%p was deleted before Session@%p"
            " was unregistered",this,*session);

        msg.data = output;
        msg.len  = strlen(output);

        printf(output);

        (*session)->send(&msg);

        Message nothingMsg;
        memset(&nothingMsg,0,sizeof(nothingMsg));
        unregisterSession(*session,nothingMsg);
    }

    // erase this entity from the multiplexer
    mux->entities.erase(id);
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
void Networking::NetworkEntity::update( Message message )
{
    #ifdef DEBUG
    printf("NetworkEntity#%d::update(\"",id);
    for(int i = 0; i < message.len; ++i)
    {
        printf("%c",((char*)message.data)[i]);
    }
    printf("\")\n");
    #endif

    mux->update(id, registeredSessions, message);
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
void Networking::NetworkEntity::registerSession( Session * session, Message message )
{
    #ifdef DEBUG
    printf("NetworkEntity#%d::registerSession(Session%p,\"",id,session);
    for(int i = 0; i < message.len; ++i)
    {
        printf("%c",((char*)message.data)[i]);
    }
    printf("\")\n");
    #endif

    silentRegister(session);
    mux->registerSession(id, type, session, message);
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
void Networking::NetworkEntity::unregisterSession( Session * session, Message message )
{
    #ifdef DEBUG
    printf("NetworkEntity#%d::unregisterSession(Session%p,\"",id,session);
    for(int i = 0; i < message.len; ++i)
    {
        printf("%c",((char*)message.data)[i]);
    }
    printf("\")\n");
    #endif

    silentUnregister(session);
    mux->unregisterSession(id, session, message);
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
    session->registeredEntities.insert(this);
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
    session->registeredEntities.erase(this);
}

