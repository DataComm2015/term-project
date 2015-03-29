//> In the main file
#include "AppWindow.h"

#include "Network/Client.h"
#include "Logic/Entities/ClientMux.h"
#include "Logic/GameScene.h"

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

    AppWindow::getInstance().setVerticalSyncEnabled(true);
    // AppWindow::getInstance().addScene(MainMenuScene::getInstance());
    std::cout << "MAIN: before addScene" << std::endl;
	  AppWindow::getInstance().addScene(new GameScene());
    std::cout << "MAIN: before run" << std::endl;
    AppWindow::getInstance().run();

    return EXIT_SUCCESS;
}
