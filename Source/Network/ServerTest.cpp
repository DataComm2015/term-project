#include <stdio.h>

#include "Server.h"
#include "Session.h"
#include "Message.h"
#include "NetworkEntity.h"
#include "NetworkEntityMultiplexer.h"

#include <string.h>
#include <unistd.h>
#include <pthread.h>

using namespace Networking;

NetworkEntity* entity0;
NetworkEntity* entity1;
Message registerMsg;
Message unregisterMsg;
Message updateMsg;

static void* routine(void* params);

class TestServer : public Server
{
public:
    TestServer()
    {
        entity0 = new NetworkEntity(0,0);

    }
    virtual void onConnect(Session* session)
    {
        entity0->registerSession(session,registerMsg);
        entity1->registerSession(session,registerMsg);
    }
    virtual void onMessage(Session* session, char* data, int len)
    {
    }
    virtual void onDisconnect(Session* session, int remote)
    {
    }
private:
};

class mux : public NetworkEntityMultiplexer
{
public:
    mux() {};
    virtual ~mux() {};
};

int main(void)
{
    NetworkEntityMultiplexer::setInstance(new mux());

    entity0 = new NetworkEntity(0,0);
    entity1 = new NetworkEntity(1,0);

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

    delete entity0;
    entity0 = 0;
    printf("entity#0 deleted\n");
    getchar();

    delete entity1;
    entity1 = 0;
    printf("entity#1 deleted\n");
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
    while(entity0 || entity1)
    {
        sleep(1);
        if(entity0 != 0)
            entity0->update(updateMsg);
        if(entity1 != 0)
            entity1->update(updateMsg);
    }
}
