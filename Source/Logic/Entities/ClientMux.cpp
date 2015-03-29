#include "ClientMux.h"

#include "../NetworkEntityPairs.h"
#include "../GameScene.h"

#include "../../Network/NetworkEntityMultiplexer.h"

#include "../../Engine/Map.h"
#include "../../Engine/Controller.h"

#include "ProperEntity.h"
#include "CommandEntity.h"
#include "ClientGameState.h"
#include "NetworkControllerEntity.h"

ClientMux::ClientMux(GameScene* gameScene, ClientLobbyScene* lobbyScene)
    :_gameScene(gameScene)
    ,_lobbyScene(lobbyScene)
{
}

ClientMux::~ClientMux()
{
}

NetworkEntity* ClientMux::onRegister(int id, int entityType, Session* session,
    Message msg)
{
    NetworkEntity* ret;

    switch(entityType)
    {
        case NET_ENT_PAIR_PLAYER_COMMAND:
        {
            ret = new CommandEntity(id,_gameScene);
            break;
        }

        // later, should parse the message to figure out what kind of game
        // entity to create that is being controlled by the NetworkController.
        case NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER:
        {
            ret = new NetworkControllerEntity(id);
            Marx::Map* cMap = ((GameScene*)_gameScene)->getcMap();
            new ProperEntity(cMap,0.0F,0.0F,(::Marx::Controller*)ret,1.0,1.0);
            break;
        }

        case NET_ENT_PAIR_SERVERGAMESTATE_CLIENTGAMESTATE:
        {
            ret = new ClientGameState(id,_gameScene,_lobbyScene);
            break;
        }
    }

    return ret;
}
