//> In the main file
#include "AppWindow.h"

#include "Logic/Event.h"
#include "Logic/KeyListener.h"
#include "Logic/ProperEntity.h"
#include "Logic/NetworkEntityPairs.h"

#include "Engine/Controller.h"

#include "Network/Client.h"
#include "Network/Session.h"
#include "Network/Message.h"
#include "Network/NetworkEntity.h"
#include "Network/NetworkEntityMultiplexer.h"

using Networking::NetworkEntityMultiplexer;
using Networking::NetworkEntity;
using Networking::Message;
using Networking::Session;
using Networking::Client;

GameScene* scene;

/////////////
// Command //
/////////////

class Command : public NetworkEntity, public KeyListener
{
public:
    Command(int id)
        :NetworkEntity(id,NET_ENT_PAIR_PLAYER_COMMAND)
    {
        scene->addKeyListener(this);
    }
    ~Command()
    {
        scene->rmKeyListener(this);
    }
protected:
    virtual void onKeyPressed(int key)
    {
        // convert keystroke into command
        int command;
        switch(key)
        {
        case sf::Keyboard::Left:
            command = MSG_T_PLAYER_COMMAND_START_MV_LEFT_COMMAND;
            break;
        case sf::Keyboard::Right:
            command = MSG_T_PLAYER_COMMAND_START_MV_RIGHT_COMMAND;
            break;
        case sf::Keyboard::Up:
            command = MSG_T_PLAYER_COMMAND_START_MV_UP_COMMAND;
            break;
        case sf::Keyboard::Down:
            command = MSG_T_PLAYER_COMMAND_START_MV_DOWN_COMMAND;
            break;
        }

        // put the command into a message to be sent over the network
        Message msg;
        msg.type = 0;
        msg.data = &command;
        msg.len  = sizeof(command);

        // send the command over the network
        update(msg);
    }
    virtual void onKeyReleased(int key)
    {
        // convert keystroke into command
        int command;
        switch(key)
        {
        case sf::Keyboard::Left:
            command = MSG_T_PLAYER_COMMAND_STOP_MV_LEFT_COMMAND;
            break;
        case sf::Keyboard::Right:
            command = MSG_T_PLAYER_COMMAND_STOP_MV_RIGHT_COMMAND;
            break;
        case sf::Keyboard::Up:
            command = MSG_T_PLAYER_COMMAND_STOP_MV_UP_COMMAND;
            break;
        case sf::Keyboard::Down:
            command = MSG_T_PLAYER_COMMAND_STOP_MV_DOWN_COMMAND;
            break;
        }

        // put the command into a message to be sent over the network
        Message msg;
        msg.type = 0;
        msg.data = &command;
        msg.len  = sizeof(command);

        // send the command over the network
        update(msg);
    }
    virtual void onUnregister(Session* session, Message message)
    {
    }
    virtual void onUpdate(Message message)
    {
    }
};

///////////////////////
// NetworkController //
///////////////////////
class NetworkController : public ::Marx::Controller, public NetworkEntity
{
public:
    NetworkController(int id)
        :NetworkEntity(id,NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER)
    {
    }
    ~NetworkController()
    {
    }
    virtual void onUpdate( Message message )
    {
        parseEventMessage(message);
    }
    virtual void onUnregister( Session * session, Message message )
    {
        parseEventMessage(message);
    }
private:
    void parseEventMessage(Message& message)
    {
        printf("NetworkController::parseEventMessage()\n");
        // switch(message.type)
        // {
        // case ::Marx::MOVE:
        // {
        //     // case message payload
        //     MoveMessage* mm = (MoveMessage*) message.data;

        //     // create event from message data
        //     MoveEvent ev(mm->x, mm->y, mm->forced);

        //     // add event to event queue
        //     addEvent(ev);
        //     break;
        // }
        // default:
        //     printf("WARNING: NetworkController::parseEventMessage received an "
        //         "unknown event type. please add new case to switch statement");
        //     fflush(stdout);
        //     break;
        // }
    }
    void sendEventMessage(Event ev)
    {
        printf("NetworkController::sendEventMessage()\n");
        // // create network message from event
        // switch(ev.type)
        // {
        // case ::Marx::MOVE:
        // {
        //     // cast event to event subclass
        //     MoveEvent* me = (MoveEvent*) &ev;

        //     // parse move event into move message
        //     MoveMessage mm;
        //     mm.x      = me->getX();
        //     mm.y      = me->getY();
        //     mm.forced = me->forced();

        //     // message to be sent over the network
        //     Message message;
        //     message.data = &mm;
        //     message.len  = sizeof(mm);
        //     message.type = ::Marx::MOVE;

        //     // send the network event
        //     update(message);
        // }
        // default:
        //     printf("WARNING: NetworkController::sendEventMessage received an "
        //         "unknown event type. please add new case to switch statement");
        //     fflush(stdout);
        //     break;
        // }
    }
};


//////////////////////////////
// NetworkEntityMultiplexer //
//////////////////////////////

class Mux : public NetworkEntityMultiplexer
{
public:
    Mux()
    {
    }
    virtual ~Mux()
    {
    }
    virtual NetworkEntity* onRegister(int id, int entityType, Session* session,
        Message msg)
    {
        NetworkEntity* ret;

        switch(entityType)
        {
        case NET_ENT_PAIR_PLAYER_COMMAND:
            ret = new Command(id);
            break;
        case NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER:
            ret = new NetworkController(id);
            // Marx::Map* cMap = ((GameScene*)scene)->getcMap();
            // new ProperEntity(cMap,0.0F,0.0F,(::Marx::Controller*)ret,1.0,1.0);
            break;
        }

        return ret;
    };
};

//////////
// Main //
//////////

int main(int argc, char* argv[])
{
    printf("USAGE: %s [REMOTE_IP] [REMOTE_PORT]\n",argv[0]);
    fflush(stdout);

    scene = new GameScene();

    NetworkEntityMultiplexer::setInstance(new Mux());

    AppWindow::getInstance().addScene(scene);

    Client* client = new Client();

    short port = atoi(argv[2]);
    client->connect(argv[1], port);

    AppWindow::getInstance().run();

    delete client;

    return 0;
}
