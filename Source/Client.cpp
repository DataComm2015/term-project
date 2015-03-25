//> In the main file
#include "AppWindow.h"
#include "Logic/GameScene.h"
#include "Network/Client.h"
#include "Network/NetworkEntityMultiplexer.h"
#include "Network/NetworkEntity.h"
#include "Engine/ClientInput.h"
#include "Network/Session.h"
#include "Network/Message.h"
#include "Engine/ProperEntity.h"
#include "Engine/Controller.h"
#include "Network/NetworkController.h"

// include the separate scene file
using Networking::NetworkEntityMultiplexer;
using Networking::NetworkEntity;
using Networking::Message;
using Networking::Session;

GameScene* scene;

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
        case CLIENT_INPUT_CLASS:
            ret = new ClientInput(id);
            break;
        case NET_CONTROLER_CLASS:
            ret = new NetworkController(id);
            Marx::Map* cMap = ((GameScene*)scene)->getcMap();
            new ProperEntity(cMap,0.0F,0.0F,(::Marx::Controller*)ret,1.0,1.0);
            break;
        }

        return ret;
    };
};

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
