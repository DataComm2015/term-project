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
}

Session::~Session()
{
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
    messages.push_back(message);
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
    for(Message* m: messages)
    {
        entityMux->onMessage(this, *m);
    }

    // delete all here or in the loop.....
}
