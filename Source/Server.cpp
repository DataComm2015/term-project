//> In the main file
#include "AppWindow.h"
#include "Usage.cpp"

#include "Logic/Event.h"
#include "Logic/ProperEntity.h"
#include "Logic/ServerGameScene.h"
#include "Logic/NetworkEntityPairs.h"

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

/**
 * the {Player} is resides the server, and is logically mapped to the {Command}
 *   class over the network, which is on the client side.
 *
 * the client sends command using {Command::update} such as move commands or
 *   others like choosing their character to the Server. such commands are
 *   handled in the {Player::onUpdate} method. and sent using the.
 */
class Player : public NetworkEntity
{
public:
    Player(Controller* serverController)
        :NetworkEntity(NET_ENT_PAIR_PLAYER_COMMAND)
    {
        this->serverController = serverController;
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
            MoveEvent event(-1,0,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_START_MV_RIGHT_COMMAND:
        {
            MoveEvent event(1,0,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_START_MV_UP_COMMAND:
        {
            MoveEvent event(0,-1,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_START_MV_DOWN_COMMAND:
        {
            MoveEvent event(0,1,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_LEFT_COMMAND:
        {
            MoveEvent event(0,0,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_RIGHT_COMMAND:
        {
            MoveEvent event(0,0,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_UP_COMMAND:
        {
            MoveEvent event(0,0,0);
            serverController->addEvent(event);
            break;
        }
        case MSG_T_PLAYER_COMMAND_STOP_MV_DOWN_COMMAND:
        {
            MoveEvent event(0,0,0);
            serverController->addEvent(event);
            break;
        }
        }
    }
private:
    /**
     * controller used to control a player in the game.
     */
    Controller* serverController;
};

//////////////////////
// ServerController //
//////////////////////

/**
 * the {ServerController} class on the server is logically mapped to a
 *   {NetworkController} on the client. other controllers such as AI controllers
 *   should inherit from the {ServerController} class, and get their entity to
 *   do stuff by using the addEvent method.
 *
 * whenever the {ServerController::addEvent} function is called, it will get its
 *   entity to do stuff. if the event should be received on the client side as
 *   well, then the event should be converted into a Networking::Message in the
 *   {ServerController::sendEventMessage} method. the same message will be
 *   received in the {NetworkController::onUpdate} function, where it needs to
 *   be handled, and converted from a message back into an event, then added to
 *   the {NetworkController's} event queue.
 */
class ServerController : public Controller, public Networking::NetworkEntity
{
public:
    ServerController()
        :NetworkEntity(NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER)
    {
    }
    virtual ~ServerController()
    {
    }
    virtual void addEvent(Event event)
    {
        Controller::addEvent(event);
        sendEventMessage(event);
    }
    void sendEventMessage(Event event)
    {
        // create network message from event
        switch(event.type)
        {
        case ::Marx::MOVE:
        {
            // cast event to event subclass
            MoveEvent* me = (MoveEvent*) &event;

            // parse move event into move message
            MoveMessage mm;
            mm.x      = me->getX();
            mm.y      = me->getY();
            mm.forced = me->forced();

            // message to be sent over the network
            Message message;
            message.data = &mm;
            message.len  = sizeof(mm);
            message.type = ::Marx::MOVE;

            // send the network event
            update(message);
            break;
        }
        default:
            printf("WARNING: NetworkController::sendEventMessage received an "
                "unknown event type. please add new case to switch statement");
            fflush(stdout);
            break;
        }
    }
    virtual void onUnregister(Session* session, Message message)
    {
    }
    virtual void onUpdate(Message msg)
    {
    }
};

//////////////////////////////
// NetworkEntityMultiplexer //
//////////////////////////////

/**
 * the server's implementation of the {NetworkEntityMultiplexer}...nothing
 *   special to do here.
 */
class Mux : public NetworkEntityMultiplexer
{
public:
    Mux() {};
    virtual ~Mux() {};
};

////////////
// Server //
////////////

/**
 * the server's implementation of the server. this thing is going to need more
 *   work.
 *
 * at the moment, it is just hard coded to create a {Player}, {ProperEntity},
 *   and {ServerController}, and register the {ServerController} and {Player}
 *   instances with the client, which will cause the client to create a
 *   {NetworkController} and {Command} instances respectively.
 */
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
        ServerController* ctrlr = new ServerController();
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

/**
 * the game loop.
 */
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
