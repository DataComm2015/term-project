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

ClientMux::ClientMux(GameScene* gameScene, ClientLobbyScene* lobbyScene, ClientScoreboardScene* scoreScene)
    :_gameScene(gameScene)
    ,_lobbyScene(lobbyScene)
    ,_scoreScene(scoreScene)
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
            command = new CommandEntity(id,_gameScene, this);
            ret = command;
            break;
        }

        case NetworkEntityPair::SERVERCONTROLLER_NETCONTROLLER:
        {
            ClientNetworkController* c = new ClientNetworkController(id);
            ret = c;
            Marx::Map* cMap = ((GameScene*)_gameScene)->getcMap();
            Entity *entity = EntityFactory::getInstance()->makeEntityFromNetworkMessage(cMap,&msg,c);
            if(msg.type == (int) ServerNetworkControllerClientNetworkControllerMsgType::FOLLOW_ME)
            {
                 _gameScene->setPlayerVessel(static_cast<Vessel*>(entity));
            }
            break;
        }

        case NetworkEntityPair::SERVERGAMESTATE_CLIENTGAMESTATE:
        {
            gameState = new ClientGameState(id, command, _gameScene, _lobbyScene, _scoreScene);
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
