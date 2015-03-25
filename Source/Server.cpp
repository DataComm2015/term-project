//> In the main file
#include "AppWindow.h"
#include "Usage.cpp"
#include "Engine/ServerGameScene.h"
#include "Network/Server.h"
#include "Network/Session.h"
#include "Network/NetworkEntityMultiplexer.h"
#include "Network/Message.h"
#include "Engine/ClientInput.h"
#include "Engine/ProperEntity.h"
#include "Engine/Controller.h"
#include "Network/NetworkController.h"

#include <string.h>

bool isRunning;
sf::Time m_elapsedTime, m_timePerFrame, m_timeSinceLastUpdate;
Scene *scene;

void run();

class mux : public Networking::NetworkEntityMultiplexer
{
public:
    mux() {};
    virtual ~mux() {};
};

class Svr : public Networking::Server
{
public:
    Svr()
    {
    }
    virtual void onConnect(Networking::Session* session)
    {
        printf("new connection\n");

        // create an entity that the new connection can use to communicate
        // commands to the server
        ClientInput* clientInput = new ClientInput();
        Networking::NetworkController* netCont = new Networking::NetworkController();

        // create an entity that the client is supposed to control
        Marx::Map* cMap = ((GameScene*)scene)->getcMap();
        new ProperEntity(cMap,0.0F,0.0F,(::Marx::Controller*)netCont,1.0,1.0);

        // create an empty message because we need one
        Networking::Message msg;
        memset(&msg,0,sizeof(msg));

        // register the client with the player object, and player controller
        clientInput->registerSession(session,msg);
        netCont->registerSession(session,msg);
    }
    virtual void onMessage(Networking::Session* session, char* data, int len)
    {
        printf("message\n");
    }
    virtual void onDisconnect(Networking::Session* session, int remote)
    {
        printf("disconnection\n");
    }
private:
};

int main( int argc, char ** argv )
{
    printf("USAGE: %s [LOCAL_PORT]\n",argv[0]);
    fflush(stdout);

    Networking::NetworkEntityMultiplexer::setInstance(new mux());
    Svr server;
    server.startServer(atoi(argv[1]));
    scene = new ServerGameScene();
    run();
    delete scene;
    return 0;
}

void run()
{
    if (!isRunning)
    {
        isRunning = true;

        sf::Clock clock;
        sf::Event event;

        // LOOP
        while (isRunning)
        {
            // TIME UPDATES
            m_elapsedTime = clock.restart();
            m_timeSinceLastUpdate += m_elapsedTime;

            // TIME PER FRAME CONTROLLED LOOP
            while (m_timeSinceLastUpdate > m_timePerFrame)
            {
                m_timeSinceLastUpdate -= m_timePerFrame;

                scene->update(m_timePerFrame);
            }
        }

        isRunning = false;
    }
}
