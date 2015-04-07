#include "ClientGameState.h"

#include "CommandEntity.h"
#include "PlayerEntity.h"

#include "../GameScene.h"
#include "../ClientLobbyScene.h"
#include "../MainMenuScene.h"
#include "../Event.h"
#include "../NetworkEntityPairs.h"

#include "../Entities/ProperEntity.h"

#include "../../AppWindow.h"

#include "../../Engine/Event.h"
#include "../../Engine/Controller.h"

#include "../../Network/Client.h"
#include "../../Network/Session.h"
#include "../../Network/NetworkEntityMultiplexer.h"

using Networking::Client;

/*------------------------------------------------------------------------------
-- FUNCTION:        ClientGameState::ClientGameState
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Eric Tsang, Calvin Rempel
--
-- PROGRAMMER:      Eric Tsang, Jeff Bayntun
--
-- INTERFACE:       ClientGameState::ClientGameState(int id,
--                      CommandEntity *command, GameScene* gameScene,
--                      ClientLobbyScene* lobbyScene)
--                  id         - id of the {NetworkEntity} to pass to base class
--                  command    - pointer to singleton {CommandEntity}.
--                  gameScene  - pointer to client's {GameScene} instance.
--                  lobbyScene - pointer to client's {LobbyScene} instance.
--
-- RETURNS:         void
--
-- NOTES:           constructor for the {ClientGameState} class. it initializes
--                  instance variables, and calls the {NetworkEntity} base
--                  constructor.
------------------------------------------------------------------------------*/
ClientGameState::ClientGameState(int id, CommandEntity *command, ClientLobbyScene* lobbyScene, ClientScoreboardScene* scoreScene)
    : NetworkEntity(id,(int)NetworkEntityPair::SERVERGAMESTATE_CLIENTGAMESTATE)
    , _lobbyScene(lobbyScene)
    , _scoreScene(scoreScene)
    , command(command)
{
    _fakeLobby = new ClientLobbyScene(true);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ClientGameState::~ClientGameState
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Eric Tsang
--
-- INTERFACE:       ClientGameState::~ClientGameState()
--
-- RETURNS:         void
--
-- NOTES:           destructor for the {ClientGameStat} class.
------------------------------------------------------------------------------*/
ClientGameState::~ClientGameState()
{
    delete _fakeLobby;
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ClientGameState::onUpdate
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Eric Tsang, Calvin Rempel
--
-- PROGRAMMER:      Eric Tsang, Calvin Rempel, Jeff Bayntun
--
-- INTERFACE:       void ClientGameState::onUpdate(Message msg)
--                  msg - network message received by the remote host
--
-- RETURNS:         void
--
-- NOTES:           used to handle network messages received from the remote
--                  host.
--
--                  this function, parses messages sent from the
--                  {ServerGameScene}.
------------------------------------------------------------------------------*/
void ClientGameState::onUpdate(Message msg)
{
    switch((ServerGameStateClientGameStateMsgType)msg.type)
    {
        /*
         * indicates to the client to send the server the user's "selections"
         *   like which character they want to play as and nickname and such.
         */
        case ServerGameStateClientGameStateMsgType::READY_FOR_GAME:
            /* Send back player lobby selections */
            command->notifyServerLobbySelections(_lobbyScene->getSelections());
            break;

        /*
         * indicates to the client to start the game scene. at this point, the
         *   player mode should have been set.
         */
        case ServerGameStateClientGameStateMsgType::START_GAME_SCENE:

            /*
             * print out the player's game mode. server has informed client of
             *   what kind of player it is before going to {GameScene}.
             */
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

            // go to the game scene, generating it with the seed sent from the
            // server
            AppWindow::getInstance().removeScene(1);
            MainMenuScene::getGameScene()->generateMap(*((int*) msg.data));
            AppWindow::getInstance().addScene(MainMenuScene::getGameScene());
            break;

        /*
         * indicates to the client to display the Lobby scene.
         */
        case ServerGameStateClientGameStateMsgType::START_LOBBY_SCENE:
            AppWindow::getInstance().removeScene(1);
            AppWindow::getInstance().addScene(_lobbyScene);
            break;

        /*
         * indicates to the client to display the fake lobby.
         */
        case ServerGameStateClientGameStateMsgType::FAKE_LOBBY:
            AppWindow::getInstance().removeScene(1);
            AppWindow::getInstance().addScene(_fakeLobby);
            break;

        /*
         * indicates to the client that a new player has connected, so the
         *   player count in the lobby should be incremented.
         */
        case ServerGameStateClientGameStateMsgType::PLAYER_CONNECTED:
            _lobbyScene->updatePlayerCount(*((int*)msg.data));
            break;

        /*
         * indicates to the client that a new player has connected, so the
         *   player count in the lobby should be decremented.
         */
        case ServerGameStateClientGameStateMsgType::PLAYER_DISCONNECTED:
            _lobbyScene->updatePlayerCount(*((int*)msg.data));
            break;

        /*
         * indicates to the client that the lobby countdown has begun.
         */
        case ServerGameStateClientGameStateMsgType::LOBBY_COUNTDOWN_START:
            _lobbyScene->startTimer(*((int*)msg.data));
            break;

        /*
         * indicates to the client that the lobby countdown has stopped.
         */
        case ServerGameStateClientGameStateMsgType::LOBBY_COUNTDOWN_STOP:
            _lobbyScene->stopTimer(*((int*)msg.data));
            break;

        case ServerGameStateClientGameStateMsgType::START_SCORE_SCENE:
            MainMenuScene::getGameScene()->stopAllSounds();
            memcpy(_scoreScene->data_received, msg.data, sizeof(Player) * 12);  
            AppWindow::getInstance().removeScene(1);
            AppWindow::getInstance().addScene(_scoreScene);
            break;
    }
}
