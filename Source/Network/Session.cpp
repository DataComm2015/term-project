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
    this->recvProcess = ReceiveProcess::getInstance();
    // SendProcess* sendProcess
    // NetworkEntityMultiplexer* entityMux
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
    printf("session: session %p:%d disconnected\n",this,socket);
}

void Session::onMessageReceived(Message *message)
{
    // entityMux->onMessage(this, message);
}

void Session::onConnectionClosedByRemote()
{
    // Handle Closed Connections
}
