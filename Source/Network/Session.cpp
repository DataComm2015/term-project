#include "Session.h"
#include "Message.h"
// #include "ReceiveProcess"
// #include "SendProcess"
// #include "NetworkEntityMultiplexer.h"

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace Networking;

Session::Session(int socket)
{
    printf("session: session %p connected\n", this);
    this->socket = socket;
    // ReceiveProcess* readProcess
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
    printf("session: session %p disconnected\n", this);
}

void Session::onMessageReceived(Message *message)
{
    // entityMux->onMessage(this, message);
}

void Session::onConnectionClosedByRemote()
{
    // Handle Closed Connections
}
