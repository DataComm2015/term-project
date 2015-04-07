#include "ClientMux.h"

#include "../NetworkEntityPairs.h"
#include "../GameScene.h"
#include "../MainMenuScene.h"

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

/*------------------------------------------------------------------------------
-- FUNCTION:        ClientMux::ClientMux
--
-- DATE:            March 31, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Team
--
-- PROGRAMMER:      Calvin Rempel, Eric Tsang
--
-- INTERFACE:       ClientMux::ClientMux(ClientLobbyScene* lobbyScene)
--                  lobbyScene - pointer to the singleton {ClientLobbyScene}.
--
-- RETURNS:         void
--
-- NOTES:           constructs a new client side {CLientMux} which inherits from
--                  {NetworkEntityMultiplexer} used to handle onRegister
--                  messages from the server.
------------------------------------------------------------------------------*/
ClientMux::ClientMux(ClientLobbyScene* lobbyScene, ClientScoreboardScene* scoreScene)
    :_lobbyScene(lobbyScene)
    ,_scoreScene(scoreScene)
{
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ClientMux::~ClientMux
--
-- DATE:            March 31, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Team
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       ClientMux::~ClientMux()
--
-- RETURNS:         void
--
-- NOTES:           destroys the {ClientMux} instance.
------------------------------------------------------------------------------*/
ClientMux::~ClientMux()
{
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ClientMux::onRegister
--
-- DATE:            March 31, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Team
--
-- PROGRAMMER:      Jeff Bayntun, Calvin Rempel, Eric Tsang
--
-- INTERFACE:       NetworkEntity* ClientMux::onRegister(int id, int entityType,
--                      Session* session, Message msg)
--                  id         - id of the {NetworkEntity} to return.
--                  entityType - indicates what kind of
--                  session    -
--                  msg        -
--
-- RETURNS:         NetworkEntity
--
-- NOTES:           handles {onRegister} type messages from the server. this
--                  should use the passed parameters to instantiate a
--                  {NetworkEntity}, and return it back to the {ClientMux}.
--
--                  it's not possible to call update from within this function,
--                  if you want to call update after onRegister, call update
--                  within the {NetworkEntity::onRegister} instead.
------------------------------------------------------------------------------*/
NetworkEntity* ClientMux::onRegister(int id, int entityType, Session* session,
    Message msg)
{
    NetworkEntity* ret;
    this->session = session;
    GameScene *_gameScene = MainMenuScene::getGameScene();

    switch((NetworkEntityPair)entityType)
    {
        case NetworkEntityPair::PLAYER_COMMAND:
        {
            command = new CommandEntity(id, this);
            ret = command;
            fprintf(stdout, "MUX NICKNAME: %s\n", message.data);
            fflush(stdout);
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
            gameState = new ClientGameState(id, command, _lobbyScene, _scoreScene);
            ret = gameState;
            break;
        }

        case NetworkEntityPair::STRUCTURE_MIRROR:
            Marx::Map* cMap = ((GameScene*)_gameScene)->getcMap();
            EntityFactory::getInstance()->makeEntityFromNetworkMessage(id, cMap,&msg,NULL);
            break;
    }

    return ret;
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ClientMux::shutdown
--
-- DATE:            March 31, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Networking Team
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       void ClientMux::shutdown()
--
-- RETURNS:         void
--
-- NOTES:           unregisters the session used to connect with the server from
--                  the server.
------------------------------------------------------------------------------*/
void ClientMux::shutdown()
{
    // create empty network message
    Message msg;
    memset(&msg,0,sizeof(msg));

    // unregister our {Session} from the server
    command->unregisterSession(session, msg);
}

CommandEntity* ClientMux::getCommandEntity()
{
  return command;
}
