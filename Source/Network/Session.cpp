#include "Session.h"
#include "Message.h"
#include "NetworkEntity.h"
#include "NetworkEntityMultiplexer.h"

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

// #define DEBUG

using namespace Networking;

Session::Session(int socket)
{
    #ifdef DEBUG
    printf("session %p connected\n",this);
    #endif
    // initialize instance variables
    this->socket    = socket;
    this->entityMux = NetworkEntityMultiplexer::getInstance();
    this->messagesSem = createSem(MESSAGE_SEM_KEY--);

    accessSem(SESSION_SEM);
    SESSIONS.insert(this);
    releaseSem(SESSION_SEM);
}

Session::~Session()
{
    accessSem(SESSION_SEM);
    SESSIONS.erase(this);
    releaseSem(SESSION_SEM);

    Message* m;
    while(!messages.empty())
    {
         auto it = messages.front();
        m = it;
        free( m );
        messages.pop_front();
    }

    disconnect();
}

void Session::send(Message* msg)
{
    int packetlen = msg->len+sizeof(msg->len)+sizeof(msg->type);
    write(socket,&packetlen,sizeof(packetlen));
    write(socket,&msg->type,sizeof(msg->type));
    write(socket,&msg->len,sizeof(msg->len));
    write(socket,msg->data,msg->len);
}

void Session::disconnect()
{
    close(socket);
}
/**
 * @brief Session::onMessage
 *          takes a message from the network and adds it to the
 *          queue for later use.
 * @param msg
 *          pointer to the message received
 *
 * @designer Network Teams
 *
 * @author Jeff Bayntun, Eric Tsang
 */
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
void Session::handleMessages()
{
    accessSem(messagesSem);
    Message* m;

    for(auto it = messages.begin(); it != messages.end(); it++)
    {
        m = *it;
        entityMux->onMessage(this, *m);
        free(*it);
        it = messages.erase(it);
    }

    releaseSem(messagesSem);
}

void handleSessionMessages()
{
    accessSem(SESSION_SEM);
    for(auto it = SESSIONS.begin(); it != SESSIONS.end(); it++)
    {
        (*it)->handleMessages();
    }
    releaseSem(SESSION_SEM);
}



