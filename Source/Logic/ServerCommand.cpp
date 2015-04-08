#include "ServerCommand.h"

#include <string.h>
#include <map>
#include <cstdio>

#include "../Network/Session.h"
#include "NetworkEntityPairs.h"
#include "Entities/ServerNetworkController.h"
#include "../Network/Message.h"
#include "../Multimedia/manager/ResourceManager.h"
#include "../Multimedia/graphics/object/SGO.h"
#include "ServerGameScene.h"
#include "ServerLobbyScene.h"

#include "Entities/ServerGameState.h"
#include "Entities/PlayerEntity.h"
#include "Entities/ProperEntity.h"

using Networking::Message;
using Networking::Session;

ServerCommand::ServerCommand()
{
    gameScene = NULL;
    lobbyScene = new ServerLobbyScene(this);
    gameState = new ServerGameState(this);
    goToLobby();
}
/**
 * @brief ServerCommand::onConnect
 * When a new client connects, this handles adding them to
 * the game
 * @param session   session that connected
 *
 * @author Calvin Rempel, Jeff Bayntun
 */
/*----------------------------------------------------------------------------------------------
-- FUNCTION:        onConnect
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:
--
-- PROGRAMMER:      Calvin Rempel, Jeff Bayntun
--
-- INTERFACE:       void ServerCommand::onConnect(Session* session)

-- RETURNS:         void
--
-- NOTES:          handles a newly connected client, directing them to the proper scene
-----------------------------------------------------------------------------------------------*/
void ServerCommand::onConnect(Session* session)
{
    // create an entity that the new connection can use to communicate
    // commands to the server
    PlayerEntity* player = new PlayerEntity(this);

    // create an empty message because we need one
    Message msg;
    memset(&msg,0,sizeof(msg));

    // register the client with the player object, and player controller
    player->registerSession(session,msg);


    // register the client with the GameState object
    gameState->registerSession(session,msg);

    // Add Player to Lobby
    lobbyScene->addPlayer();
    gameState->playerJoined(session, player);

    // If game is not in progress -> go to lobby
    if (activeScene == lobbyScene)
    {
        gameState->goToLobby();
    }
    // If game is in progress -> go to a fake lobby to wait for end of match
    else
    {
        player->setMode(PLAYER_MODE::GHOST);
        Message fake_lobby;
        fake_lobby.type = (int)ServerGameStateClientGameStateMsgType::FAKE_LOBBY;
        fake_lobby.data = (void*) session;
        fake_lobby.len = strlen((char*)fake_lobby.data);

        gameState->update(fake_lobby);
    }

}

void ServerCommand::onMessage(Session* session, char* data, int len)
{


}

void ServerCommand::onDisconnect(Session* session, int remote)
{
}

Scene *ServerCommand::getActiveScene()
{
    return activeScene;
}

ServerGameState *ServerCommand::getGameState()
{
    return gameState;
}

ServerGameScene *ServerCommand::getGameScene()
{
    return gameScene;
}

bool ServerCommand::isGameInProgress()
{
    return activeScene == gameScene;
}

void ServerCommand::goToLobby()
{
    activeScene = lobbyScene;
    lobbyScene->enterScene();
    gameState->goToLobby();
}

void ServerCommand::goToScoreboard()
{
    gameState->goToScoreboard();
}

void ServerCommand::prepareForGameState()
{
    gameState->prepareForGameState();
}

void ServerCommand::goToGame()
{
    if (!isGameInProgress())
        gameScene = new ServerGameScene(this);
    activeScene = gameScene;
    gameScene->enterScene();
}

void ServerCommand::playerLeft(Session *session)
{
    gameState->playerLeft(session);
    lobbyScene->removePlayer();
}
