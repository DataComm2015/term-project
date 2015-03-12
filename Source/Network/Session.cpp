#include "Session.h"
#include "Message.h"
#include "ReceiveProcess.h"
// #include "SendProcess"
// #include "NetworkEntityMultiplexer.h"

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace Networking;

Session::Session()
{
    printf("session: session %p connected\n",this);

    // initialize instance variables
    // this->recvProcess = ReceiveProcess::getInstance();
    // SendProcess* sendProcess
    // NetworkEntityMultiplexer* entityMux

    // recvProcess->addSession(this);
}

Session::~Session()
{
    disconnect();
}

void Session::send(Message *message)
{
    // sendProcess->send(message);
}

void Session::disconnect()
{
    // printf("session: session %p disconnected\n",this);
    // recvProcess->removeSession(this);
}

void Session::onMessageReceived(Message* msg)
{
    printf("server: socket %p: ",this);
    for(int i = 0; i < msg->len; ++i)
    {
        printf("%c",((char*)msg->data)[i]);
    }
    printf("\n");
}

void Session::onDisconnect(int remote)
{
    printf("server: session %p disconnected by %s host\n",this,remote?"remote":"local");
}
