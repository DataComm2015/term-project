#include "Session.h"
#include "Message.h"
#include "NetworkEntityMultiplexer.h"

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace Networking;

Session::Session(int socket)
{
    printf("session %p connected\n",this);

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
    printf("session %p: ",this);
    for(int i = 0; i < msg->len; ++i)
    {
        printf("%c",*(((char*)msg->data)+i));
    }
    printf("\n");
    this->entityMux->onMessage(this,*msg);
}

void Session::onDisconnect(int remote)
{
    printf("session %p disconnected by %s host\n",this,remote?"remote":"local");
}
