#include "ServerCommand.h"

#include <string.h>
#include <map>

#include "../Network/Session.h"
#include "NetworkEntityPairs.h"
#include "Entities/ServerCommandEntity.h"
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
    gameScene = new ServerGameScene(this);
    lobbyScene = new ServerLobbyScene(this);
    gameState = new ServerGameState(this);
    goToLobby();
}

void ServerCommand::onConnect(Session* session)
{
    printf("new connection\n");

    // create an entity that the new connection can use to communicate
    // commands to the server
    ServerCommandEntity* ctrlr = new ServerCommandEntity();
    PlayerEntity* player = new PlayerEntity(ctrlr);

    // create an empty message because we need one
    Message msg;
    memset(&msg,0,sizeof(msg));

    // register the client with the player object, and player controller
    player->registerSession(session,msg);
    
    // register the client with the GameState object
    gameState->registerSession(session,msg);

    // create an entity that the client is supposed to control
    //Marx::Map* cMap = ((ServerGameScene*)scene)->getcMap();

    ctrlr->registerSession(session,msg);
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

void ServerCommand::goToLobby()
{
    activeScene = lobbyScene;
    lobbyScene->enterScene();
    gameState->goToLobby();
}

void ServerCommand::goToGame()
{
    activeScene = gameScene;
    gameScene->enterScene();
    gameState->goToGame();
}
