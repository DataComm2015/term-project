#include "Session.h"
#include "Message.h"
#include "ReceiveProcess.h"
// #include "SendProcess"
// #include "NetworkEntityMultiplexer.h"

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace Networking;

Session::Session(int socket)
{
    printf("session: session %p:%d connected\n",this,socket);

    // initialize instance variables
    this->socket = socket;
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
    close(socket);
    // recvProcess->removeSession(this);
    printf("session: session %p:%d disconnected\n",this,socket);
}

void Session::onMessageReceived(Message* msg)
{
    printf("Session::onMessageReceived %.*s\n",msg->len,msg->data);
}

void Session::onConnectionClosedByRemote()
{
    printf("Session::onConnectionClosedByRemote\n");
}
