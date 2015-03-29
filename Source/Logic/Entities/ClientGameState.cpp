#include "ClientGameState.h"

#include "../../AppWindow.h"

#include "../../Engine/Event.h"
#include "../../Engine/Controller.h"

#include "../Entities/ProperEntity.h"

#include "../GameScene.h"
#include "../ClientLobbyScene.h"
#include "../Event.h"
#include "../NetworkEntityPairs.h"



#include "../../Network/Client.h"
#include "../../Network/Session.h"
#include "../../Network/NetworkEntityMultiplexer.h"

using Networking::Client;

ClientGameState::ClientGameState(int id, GameScene* gameScene, ClientLobbyScene* lobbyScene)
    :NetworkEntity(id,NET_ENT_PAIR_SERVERGAMESTATE_CLIENTGAMESTATE)
    ,_gameScene(gameScene)
    ,_lobbyScene(lobbyScene)
{
}

ClientGameState::~ClientGameState()
{
}

void ClientGameState::onUnregister(Session* session, Message msg)
{
    // Do Nothing
}

void ClientGameState::onUpdate(Message msg)
{
    switch(msg.type)
    {
    case MSG_T_SERVERGAMESTATE_CLIENTGAMESTATE_START_GAME_SCENE:
        AppWindow::getInstance().removeScene(1);
        AppWindow::getInstance().setVerticalSyncEnabled(true);
        AppWindow::getInstance().addScene(_gameScene);
        AppWindow::getInstance().run();
        break;
    case MSG_T_SERVERGAMESTATE_CLIENTGAMESTATE_START_LOBBY_SCENE:
        AppWindow::getInstance().removeScene(1);
        AppWindow::getInstance().setVerticalSyncEnabled(true);
        AppWindow::getInstance().addScene(_lobbyScene);
        AppWindow::getInstance().run();
        break;
    }
}
