/*------------------------------------------------------------------------------
-- FILE:            Session.cpp
--
-- DATE:            March 17, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Network Teams
--
-- PROGRAMMER:      Eric Tsang, Jeff Bayntun, Calvin Rempel
--
-- INTERFACE:       Session(int socket);
                    virtual ~Session();
                    void send(Message* msg);
                    void disconnect();
                    void onMessage(Message* msg);
                    void onDisconnect(int remote);
                    void handleMessages();
                    void markForDeletion();

--
-- NOTES:           the {ServerNetworkController} class on the server is logically mapped to a
                    {ClientNetworkController} on the client. other controllers such as AI
                    controllers should inherit from the {ClientNetworkController} class, and
                    get their entity to do stuff by using the addEvent method.
------------------------------------------------------------------------------*/

#include "Session.h"
#include "Message.h"
#include "semaphores.h"
#include "NetworkEntity.h"
#include "NetworkEntityMultiplexer.h"


#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

// #define DEBUG

using namespace Networking;

static int SESSION_SET_SEM_KEY = rand() % 5000 + 11;
static int SESSION_SEM = initSessionSem(SESSION_SET_SEM_KEY);
static int MESSAGE_SEM_KEY = 9956;
static std::set<Session*> SESSIONS;
static std::set<Session*> sessionsToDelete;

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        Session::Session(int socket)
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       Session(int socket)
                    socket for this session

-- RETURNS:         void
--
-- NOTES:           Creates a Session
-----------------------------------------------------------------------------------------------*/
Session::Session(int socket)
{
    #ifdef DEBUG
    printf("session %p connected\n",this);
    #endif
    // initialize instance variables
    this->socket    = socket;
    this->entityMux = NetworkEntityMultiplexer::getInstance();
    this->messagesSem = createSem(MESSAGE_SEM_KEY--);
    releaseSem(messagesSem);

    accessSem(SESSION_SEM);
    SESSIONS.insert(this);
    releaseSem(SESSION_SEM);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        Session::~Session()
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Teams
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       ~Session()

-- RETURNS:         void
--
-- NOTES:           destroys a Session
-----------------------------------------------------------------------------------------------*/
Session::~Session()
{
    SESSIONS.erase(this);

    Message* m;
    while(!messages.empty())
    {
         auto it = messages.front();
        m = it;
        free(m->data);
        delete m;
        messages.pop_front();
    }
    deleteSem(messagesSem);
    disconnect();
}
/*----------------------------------------------------------------------------------------------
-- FUNCTION:        send
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE:       void Session::send(Message* msg)

-- RETURNS:         void
--
-- NOTES:
-----------------------------------------------------------------------------------------------*/
void Session::send(Message* msg)
{
    int packetlen = msg->len+sizeof(msg->len)+sizeof(msg->type);
    write(socket,&packetlen,sizeof(packetlen));
    write(socket,&msg->type,sizeof(msg->type));
    write(socket,&msg->len,sizeof(msg->len));
    write(socket,msg->data,msg->len);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        disconnect
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE:       void Session::disconnect()

-- RETURNS:         void
--
-- NOTES:
-----------------------------------------------------------------------------------------------*/
void Session::disconnect()
{
    close(socket);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        onMessage
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Network Teams
--
-- PROGRAMMER:      Jeff Bayntun, Eric Tsang
--
-- INTERFACE:       void Session::onMessage(Message* msg)

-- RETURNS:         void
--
-- NOTES:           takes a message from the network and adds it to the
                      queue for later use.
-----------------------------------------------------------------------------------------------*/
void Session::onMessage(Message* msg)
{
    #ifdef DEBUG
    printf("session %p: %d:",this,msg->type);
    for(int i = 0; i < msg->len; ++i)
    {
        printf("%c",*(((char*)msg->data)+i));
    }
    printf("\n");
    #endif

    Message* message = new Message;
    message->type = msg->type;
    message->len = msg->len;
    message->data = malloc(message->len);
    memcpy(message->data, msg->data, message->len);

    accessSem(messagesSem);
    messages.push_back(message);
    releaseSem(messagesSem);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        disconnect
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE:       void Session::disconnect()

-- RETURNS:         void
--
-- NOTES:
-----------------------------------------------------------------------------------------------*/
void Session::onDisconnect(int remote)
{
    #ifdef DEBUG
    printf("session %p disconnected by %s host\n",this,remote?"remote":"local");
    #endif
    for(auto entity = registeredEntities.begin();
        entity != registeredEntities.end(); ++entity)
    {
        printf("WARNING: Session@%p was disconnected before "
            "NetworkEntity@%p was unregistered\n",this,*entity);
        (*entity)->silentUnregister(this);
    }
}
/**
 * @brief Session::handleMessages
 *              passes all queued messages to the mux
 *              should messages be deleted after mux pass??
 *
 * @designer Jeff Baytun
 * @author   Jeff Bayntun
 *
 */
/*----------------------------------------------------------------------------------------------
-- FUNCTION:        handleMessages
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void Session::handleMessages()

-- RETURNS:         void
--
-- NOTES:           iterates through the messages for this session and sends them to the
                    muxxer
-----------------------------------------------------------------------------------------------*/
void Session::handleMessages()
{
    accessSem(messagesSem);
    Message* m;

  //  printf("actual mesages %d\n", messages.size());
    while(messages.size() > 0)
    {
        m = messages[0];
       // printf("before entitymux onMessage\n");
        entityMux->onMessage(this, *m);
       // printf("after entitymux onMessage\n");
        free(m->data);
        delete m;
        messages.erase(messages.begin());
    }

    releaseSem(messagesSem);
   // printf("end actual messages");
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        handleSessionMessages
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void Session::handleSessionMessages()

-- RETURNS:         void
--
-- NOTES:           iterates through the sessions telling them to iterate through
                    their current received messages from the network.
-----------------------------------------------------------------------------------------------*/
void Networking::handleSessionMessages()
{
    // obtain synchronization objects
    accessSem(SESSION_SEM);

    // handle all pending messages
    for(auto it = SESSIONS.begin(); it != SESSIONS.end(); it++)
    {
        (*it)->handleMessages();
    }

    // delete all sessions marked for deletion
    while(sessionsToDelete.size() > 0)
    {
        delete *(sessionsToDelete.begin());
        sessionsToDelete.erase(*(sessionsToDelete.begin()));
    }

    // release synchronization objects
    releaseSem(SESSION_SEM);
}

/*----------------------------------------------------------------------------------------------
-- FUNCTION:        markForDeletion
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:
--
-- PROGRAMMER:
--
-- INTERFACE:       void Session::markForDeletion()

-- RETURNS:         void
--
-- NOTES:
-----------------------------------------------------------------------------------------------*/
void Session::markForDeletion()
{
    // obtain synchronization objects
    accessSem(SESSION_SEM);

    // mark the session for deletion
    sessionsToDelete.insert(this);

    // release synchronization objects
    releaseSem(SESSION_SEM);
}
