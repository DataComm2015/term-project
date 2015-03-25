//> In the main file
#include "AppWindow.h"

#include "Logic/KeyListener.h"
#include "Logic/NetworkEntityPairs.h"

#include "Engine/Controller.h"
#include "Engine/ProperEntity.h"

#include "Network/Client.h"
#include "Network/Session.h"
#include "Network/Message.h"
#include "Network/NetworkEntity.h"
#include "Network/NetworkController.h"
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
        printf("Command::onKeyPressed: %d\n",key);
    }
    virtual void onKeyReleased(int key)
    {
        printf("Command::onKeyReleased: %d\n",key);
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
        // case NET_ENT_PAIR_PLAYERCONTROLLER_NETCONTROLLER:
        //     ret = new NetworkController(id);
        //     Marx::Map* cMap = ((GameScene*)scene)->getcMap();
        //     new ProperEntity(cMap,0.0F,0.0F,(::Marx::Controller*)ret,1.0,1.0);
        //     break;
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
