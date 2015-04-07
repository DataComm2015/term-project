/*------------------------------------------------------------------------------
-- FILE:        ClientNetworkController.cpp
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Network Teams
--
-- PROGRAMMER:      Jeff Bayntun, Eric Tsang
--
-- INTERFACE:       NetworkEntity(int id, int type);
                    NetworkEntity(int type);
                    virtual ~NetworkEntity();
                    virtual void update(Message message);
                    void registerSession(Session * session, Message message);
                    void unregisterSession(Session * session, Message message);
                    int getType();
                    int getId();
                    virtual void onRegister(Session *session);
                    virtual void onUnregister(Session * session, Message message);
                    virtual void onUpdate(Message message);
                    int silentRegister(Session* session);
                    int silentUnregister(Session* session);

-- RETURNS:         void
--
-- NOTES:           the {ServerNetworkController} class on the server is logically mapped to a
                    {ClientNetworkController} on the client. other controllers such as AI
                    controllers should inherit from the {ClientNetworkController} class, and
                    get their entity to do stuff by using the addEvent method.
------------------------------------------------------------------------------*/

#include "NetworkEntity.h"
#include "Session.h"
#include "NetworkEntityMultiplexer.h"
#include "Message.h"

#include <string.h>

// #define DEBUG

using namespace std;

int Networking::NetworkEntity::nextId = 0;

Networking::NetworkEntity::NetworkEntity( int type )
    :NetworkEntity(nextId++,type)
{
}

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
-- INTERFACE:       NetworkEntity::NetworkEntity( int id, int type )
--                  id: the id of this network entity
                    type: they type of this network entity

-- RETURNS:         void
--
-- NOTES:           Creates a NetworkEntity object
-----------------------------------------------------------------------------------------------*/
Networking::NetworkEntity::NetworkEntity( int id_, int type_ )
    : id(id_)
    , type(type_)
{
    this->mux = NetworkEntityMultiplexer::getInstance();

    // add this entity to the multiplexer
    mux->entities[id] = this;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        NetworkEntity::~NetworkEntity
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:
--
-- INTERFACE:       NetworkEntity::~NetworkEntity()

-- RETURNS:         void
--
-- NOTES:           destructs a network entity
-----------------------------------------------------------------------------------------------*/
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

    if(silentRegister(session))
    {
        mux->registerSession(id, type, session, message);
    }
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

    if(silentUnregister(session))
    {
        mux->unregisterSession(id, session, message);
    }
}

int Networking::NetworkEntity::getType()
{
    return type;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        NetworkEntity::onRegister
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       NetworkEntity::onRegister();
--                  session: session that has been registered to the entity
--
-- RETURNS:         void
--
-- NOTES:           Meant to be overwritten by the user. Called when the entity
--                  is registered with a pair.
-----------------------------------------------------------------------------------------------*/
void Networking::NetworkEntity::onRegister(Session *session)
{
}

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
int Networking::NetworkEntity::silentRegister( Session* session )
{
    int hasSession = (registeredSessions.find(session) == registeredSessions.end());
    if(hasSession)
    {
        registeredSessions.insert(session);
        session->registeredEntities.insert(this);
    }
    return hasSession;
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
int Networking::NetworkEntity::silentUnregister( Session* session )
{
    int hasSession = (registeredSessions.find(session) != registeredSessions.end());
    if(hasSession)
    {
        registeredSessions.erase(session);
        session->registeredEntities.erase(this);
    }
    return hasSession;
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        NetworkEntity::getID
--
-- DATE:            March 30, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Thomas Tallentire
--
-- PROGRAMMER:      Thomas Tallentire
--
-- INTERFACE:       int NetworkEntity::getId()
--
-- PARAMETER:		
--
-- RETURNS:         id - The id of this networkentity
--
-- NOTES:           Function returns the id of the networkEntity
-----------------------------------------------------------------------------------------------*/
int Networking::NetworkEntity::getId()
{
	return id;
}

