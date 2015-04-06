//> In the main file
#include "AppWindow.h"

#include "Network/Client.h"

#include "Logic/Entities/ClientMux.h"
#include "Logic/EntityFactory.h"
#include "Engine/ProjectileManager.h"
#include "Logic/GameScene.h"

using Networking::NetworkEntityMultiplexer;
using Networking::Client;

//////////
// Main //
//////////

int main(int argc, char* argv[])
{
    // force the entity factory to create their graphics on the main thread
    EntityFactory::getInstance();

    AppWindow::getInstance().setVerticalSyncEnabled(true);

    //AppWindow::getInstance().setKeyRepeatEnabled(false);

    AppWindow::getInstance().addScene(MainMenuScene::getInstance());
    //AppWindow::getInstance().addScene(ClientScoreboardScene::getInstance());

    AppWindow::getInstance().run();

    return EXIT_SUCCESS;
}
