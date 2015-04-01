#include "ClientGameState.h"

#include "../../AppWindow.h"

#include "../../Engine/Event.h"
#include "../../Engine/Controller.h"

#include "../Entities/ProperEntity.h"

#include "../GameScene.h"
#include "../ClientLobbyScene.h"
#include "../Event.h"
#include "../NetworkEntityPairs.h"
#include "CommandEntity.h"
#include "PlayerEntity.h"


#include "../../Network/Client.h"
#include "../../Network/Session.h"
#include "../../Network/NetworkEntityMultiplexer.h"

using Networking::Client;

ClientGameState::ClientGameState(int id, CommandEntity *command, GameScene* gameScene, ClientLobbyScene* lobbyScene, ClientScoreboardScene* scoreScene)
    : command(command)
    ,NetworkEntity(id,(int)NetworkEntityPair::SERVERGAMESTATE_CLIENTGAMESTATE)
    ,_gameScene(gameScene)
    ,_lobbyScene(lobbyScene)
    ,_scoreScene(scoreScene)
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
    switch((ServerGameStateClientGameStateMsgType)msg.type)
    {
        case ServerGameStateClientGameStateMsgType::READY_FOR_GAME:
            /* Send back player lobby selections */
            command->notifyServerLobbySelections(_lobbyScene->getSelections());
            break;

        case ServerGameStateClientGameStateMsgType::START_GAME_SCENE:

            /* Server has informed client of what kind of player it is before going to GameScene */
            switch((PLAYER_MODE)command->getPlayerMode())
            {
                case PLAYER_MODE::VESSEL:
                    printf("VESSEL\n");
                    break;

                case PLAYER_MODE::DEITY:
                    printf("DEITY\n");
                    break;

                case PLAYER_MODE::GHOST:
                    printf("GHOST\n");
                    break;

                default:
                    printf("NO TYPE SET\n");
                    break;
            }

            AppWindow::getInstance().removeScene(1);
            _gameScene->generateMap(*((int*) msg.data));
            AppWindow::getInstance().addScene(_gameScene);
            break;
        case ServerGameStateClientGameStateMsgType::START_LOBBY_SCENE:
            AppWindow::getInstance().removeScene(1);
            AppWindow::getInstance().addScene(_lobbyScene);
            break;
        case ServerGameStateClientGameStateMsgType::PLAYER_CONNECTED:
            _lobbyScene->updatePlayerCount(*((int*)msg.data));
            break;
        case ServerGameStateClientGameStateMsgType::PLAYER_DISCONNECTED:
            _lobbyScene->updatePlayerCount(*((int*)msg.data));
            break;

        case ServerGameStateClientGameStateMsgType::LOBBY_COUNTDOWN_START:
            _lobbyScene->startTimer(*((int*)msg.data));
            break;

        case ServerGameStateClientGameStateMsgType::LOBBY_COUNTDOWN_STOP:
            _lobbyScene->stopTimer(*((int*)msg.data));
            break;

        case ServerGameStateClientGameStateMsgType::START_SCORE_SCENE:
            AppWindow::getInstance().removeScene(1);
            AppWindow::getInstance().addScene(_scoreScene);
            break;
    }
}
