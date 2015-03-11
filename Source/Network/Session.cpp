#include "Session.h"

#include "ReceiveProcess"
#include "SendProcess"
#include "NetworkEntityMultiplexer.h"
#include "Message.h"

#include <sys/socket.h>

Networking::Session::Session(unsigned int socket, ReceiveProcess *readProcess,
    SendProcess *sendProcess, NetworkEntityMultiplexer *entityMux)
    : socket(socket), readProcess(readProcess), sendProcess(sendProcess),
    entityMux(entityMux)
{
    // Nothing to do
}

Networking::Session::~Session()
{
    disconnect();
}

unsigned int Networking::Session::getSocket()
{
    return socket;
}

void Networking::Session::send(Message *message)
{
    sendProcess->send(message);
}

void Networking::Session::disconnect()
{
    close(socket);
}

void onMessageReceived(Message *message)
{
    entityMux->onMessage(this, message);
}

void onConnectionClosedByRemote()
{
    // Handle Closed Connections
}
