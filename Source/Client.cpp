//> In the main file
#include "AppWindow.h"
#include "Logic/GameScene.h"
#include "Network/Client.h"
#include "Network/NetworkEntityMultiplexer.h"
// include the separate scene file
using namespace Networking;

class mux : public NetworkEntityMultiplexer
{
public:
    mux() {};
    virtual ~mux() {};
};

int main(int argc, char* argv[])
{
    GameScene scene1;

    NetworkEntityMultiplexer::setInstance(new mux());

    AppWindow::getInstance().addScene(&scene1);

    Client* client = new Client();

    short port = atoi(argv[2]);
    client->connect(argv[1], port);

    AppWindow::getInstance().run();

    delete client;

    return 0;
}
