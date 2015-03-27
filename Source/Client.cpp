//> In the main file
#include "AppWindow.h"

#include "Network/Client.h"
#include "Logic/Entities/ClientMux.h"

using Networking::NetworkEntityMultiplexer;
using Networking::Client;

//////////
// Main //
//////////

int main(int argc, char* argv[])
{
    // Print Launch Instructions
    printf("USAGE: %s [REMOTE_IP] [REMOTE_PORT]\n",argv[0]);
    fflush(stdout);

    GameScene *scene = new GameScene();

    // Initialize a Client Entity Multiplexer
    NetworkEntityMultiplexer::setInstance(new ClientMux(scene));
    
    Client* client = new Client();
    short port = atoi(argv[2]);
    client->connect(argv[1], port);

    AppWindow::getInstance().setVerticalSyncEnabled(true);
	AppWindow::getInstance().addScene(scene);
    AppWindow::getInstance().run();

    return EXIT_SUCCESS;
}
