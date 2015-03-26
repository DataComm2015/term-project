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

/**
 * the {Player} is resides the server, and is logically mapped to the {Command}
 *   class over the network, which is on the client side.
 *
 * the client sends command using {Command::update} such as move commands or
 *   others like choosing their character to the Server. such commands are
 *   handled in the {Player::onUpdate} method. and sent using the.
 */
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

        // bail out if we don't recognize the command
        default:
            return;
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

        // bail out if we don't recognize the command
        default:
            return;
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
        switch(message.type)
        {
        case ::Marx::MOVE:
        {
            // case message payload
            MoveMessage* mm = (MoveMessage*) message.data;

            // create event from message data
            MoveEvent ev(mm->x, mm->y, mm->forced);

            // add event to event queue
            addEvent(ev);
            break;
        }
        default:
            printf("WARNING: NetworkController::parseEventMessage received an "
                "unknown event type. please add new case to switch statement");
            fflush(stdout);
            break;
        }
    }
};


//////////////////////////////
// NetworkEntityMultiplexer //
//////////////////////////////

/**
 * the client's implementation of the {NetworkEntityMultiplexer}. this thing is
 *   going to need more work.
 *
 * when the server registers the {ServerController} and {Player} instances with
 *   the client, {Mux::onRegister} will be triggered which. it should create a
 *   {NetworkController} and {Command} instances respectively.
 */
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

        // later, should parse the message to figure out what kind of game
        // entity to create that is being controlled by the NetworkController.
        case NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER:
            ret = new NetworkController(id);
            Marx::Map* cMap = ((GameScene*)scene)->getcMap();
            new ProperEntity(cMap,0.0F,0.0F,(::Marx::Controller*)ret,1.0,1.0);
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
