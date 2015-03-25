//> In the main file
#include "AppWindow.h"
#include "Usage.cpp"

#include "Logic/NetworkEntityPairs.h"
#include "Logic/ServerGameScene.h"
#include "Logic/Event.h"

#include "Engine/ProperEntity.h"
#include "Engine/Controller.h"

#include "Network/Server.h"
#include "Network/Session.h"
#include "Network/Message.h"
#include "Network/NetworkController.h"
#include "Network/NetworkEntityMultiplexer.h"

#include <string.h>

// namespace
using Networking::NetworkEntityMultiplexer;
using Networking::NetworkController;
using Networking::NetworkEntity;
using Networking::Message;
using Networking::Session;
using Networking::Server;

// globals
bool isRunning;
sf::Time m_elapsedTime;
sf::Time m_timePerFrame;
sf::Time m_timeSinceLastUpdate;
Scene *scene;

void run();

////////////
// Player //
////////////

class Player : public NetworkEntity
{
public:
    Player(Controller* playerController)
        :NetworkEntity(NET_ENT_PAIR_PLAYER_COMMAND)
    {
        this->playerController = playerController;
    }
    virtual ~Player()
    {
    }
protected:
    virtual void onUnregister(Session* session, Message msg)
    {
    }
    virtual void onUpdate(Message msg)
    {
        switch(msg.type)
        {
        case MSG_T_PLAYER_COMMAND_START_MV_LEFT_COMMAND:
        {
            MoveEvent ev(-1,0,0);
            playerController->addEvent(ev);
            break;
        }
        case MSG_T_PLAYER_COMMAND_START_MV_RIGHT_COMMAND:
        {
            MoveEvent ev(1,0,0);
            playerController->addEvent(ev);
            break;
        }
        case MSG_T_PLAYER_COMMAND_START_MV_UP_COMMAND:
        {
            MoveEvent ev(0,-1,0);
            playerController->addEvent(ev);
            break;
        }
        case MSG_T_PLAYER_COMMAND_START_MV_DOWN_COMMAND:
        {
            MoveEvent ev(0,1,0);
            playerController->addEvent(ev);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_LEFT_COMMAND:
        {
            MoveEvent ev(0,0,0);
            playerController->addEvent(ev);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_RIGHT_COMMAND:
        {
            MoveEvent ev(0,0,0);
            playerController->addEvent(ev);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_UP_COMMAND:
        {
            MoveEvent ev(0,0,0);
            playerController->addEvent(ev);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_DOWN_COMMAND:
        {
            MoveEvent ev(0,0,0);
            playerController->addEvent(ev);
            break;
        }
        }
    }
private:
    /**
     * controller used to control a player in the game.
     */
    Controller* playerController;
};

//////////////////////
// PlayerController //
//////////////////////

class PlayerController : public Controller, public Networking::NetworkEntity
{
public:
    PlayerController()
        :NetworkEntity(NET_ENT_PAIR_PLAYER_COMMAND)
    {
    }
    virtual ~PlayerController()
    {
    }

};

//////////////////////////////
// NetworkEntityMultiplexer //
//////////////////////////////

class Mux : public NetworkEntityMultiplexer
{
public:
    Mux() {};
    virtual ~Mux() {};
};

////////////
// Server //
////////////

class Svr : public Server
{
public:
    Svr()
    {
    }
    virtual void onConnect(Session* session)
    {
        printf("new connection\n");

        // create an entity that the new connection can use to communicate
        // commands to the server
        PlayerController* ctrlr = new PlayerController();
        Player* player = new Player(ctrlr);

        // create an entity that the client is supposed to control
        Marx::Map* cMap = ((ServerGameScene*)scene)->getcMap();
        new ProperEntity(cMap,0.0F,0.0F,(::Marx::Controller*)ctrlr,1.0,1.0);

        // create an empty message because we need one
        Message msg;
        memset(&msg,0,sizeof(msg));

        // register the client with the player object, and player controller
        player->registerSession(session,msg);
        ctrlr->registerSession(session,msg);
    }
    virtual void onMessage(Session* session, char* data, int len)
    {
    }
    virtual void onDisconnect(Session* session, int remote)
    {
    }
private:
};

//////////
// main //
//////////

int main( int argc, char ** argv )
{
    printf("USAGE: %s [LOCAL_PORT]\n",argv[0]);
    fflush(stdout);

    NetworkEntityMultiplexer::setInstance(new Mux());
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
