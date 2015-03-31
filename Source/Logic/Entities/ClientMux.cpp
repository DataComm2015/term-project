#include "ClientMux.h"

#include "../NetworkEntityPairs.h"
#include "../GameScene.h"

#include "../../Network/NetworkEntityMultiplexer.h"

#include "../../Engine/Map.h"
#include "../../Engine/Controller.h"

#include "../EntityFactory.h"
#include "../EnemyControllerInit.h"
#include "../EntityTypes.h"

#include "CommandEntity.h"
#include "ClientGameState.h"
#include "ClientNetworkController.h"

#include <cstring>

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
    this->session = session;

    switch((NetworkEntityPair)entityType)
    {
        case NetworkEntityPair::PLAYER_COMMAND:
        {
            command = new CommandEntity(id,_gameScene);
            ret = command;
            break;
        }

        case NetworkEntityPair::SERVERCONTROLLER_NETCONTROLLER:
        {
            ClientNetworkController* c = new ClientNetworkController(id);
            ret = c;
            printf("ClientMux::onRegister:ret %p:%d\n",c,c->getEvents()->size());
            Marx::Map* cMap = ((GameScene*)_gameScene)->getcMap();
            EntityFactory::getInstance()->makeEntityFromNetworkMessage(cMap,&msg,c);
            break;
        }

        case NetworkEntityPair::SERVERGAMESTATE_CLIENTGAMESTATE:
        {
            gameState = new ClientGameState(id, command, _gameScene, _lobbyScene);
            ret = gameState;
            break;
        }
    }

    return ret;
}

void ClientMux::shutdown()
{
    Message msg;
    memset(&msg,0,sizeof(msg));

    command->unregisterSession(session, msg);
}
