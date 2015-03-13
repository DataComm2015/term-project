#include <stdio.h>

#include "Server.h"
#include "Message.h"
#include "NetworkEntity.h"
#include "NetworkEntityMultiplexer.h"

#include <string.h>
#include <unistd.h>
#include <pthread.h>

using namespace Networking;

NetworkEntity* entity = new NetworkEntity(0,0);
Message registerMsg;
Message unregisterMsg;
Message updateMsg;

static void* routine(void* params);

class TestServer : public Server
{
public:
    TestServer()
    {
        entity = new NetworkEntity(0,0);

    }
    virtual void onConnect(int socket)
    {
        Server::onConnect(socket);
        entity->registerSession(getSession(socket),registerMsg);
    }
    virtual void onMessage(int socket, char* data, int len)
    {
        Server::onMessage(socket,data,len);
    }
    virtual void onDisconnect(int socket, int remote)
    {
        entity->unregisterSession(getSession(socket),unregisterMsg);
        Server::onDisconnect(socket,remote);
    }
private:
};

int main(void)
{
    registerMsg.type = 0;
    registerMsg.data = (void*) "registering123";
    registerMsg.len  = strlen((char*)registerMsg.data);

    unregisterMsg.type = 0;
    unregisterMsg.data = (void*) "unregistering123";
    unregisterMsg.len  = strlen((char*)unregisterMsg.data);

    updateMsg.type = 0;
    updateMsg.data = (void*) "updating123";
    updateMsg.len  = strlen((char*)updateMsg.data);

    TestServer* svr = new TestServer();

    pthread_t thread;
    pthread_create(&thread,0,routine,0);

    svr->startServer(7000);
    printf("server started\n");
    getchar();

    svr->stopServer();
    printf("server stopped\n");
    getchar();

    delete svr;
    printf("server deleted\n");
    getchar();

    return 0;
}

static void* routine(void* params)
{
    while(1)
    {
        sleep(1);
        entity->update(updateMsg);
    }
}
