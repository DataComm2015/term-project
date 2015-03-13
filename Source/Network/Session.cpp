#include "Session.h"
#include "Message.h"
#include "NetworkEntity.h"
#include "NetworkEntityMultiplexer.h"

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define DEBUG

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
    entityMux->onMessage(this,*msg);
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
