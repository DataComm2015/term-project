#include "ServerGameState.h"

#include <cstring>
#include "../ServerCommand.h"
#include "../NetworkEntityPairs.h"

using Networking::NetworkEntity;
using Networking::Session;
using Networking::Message;

ServerGameState::ServerGameState(ServerCommand *command)
    : NetworkEntity(NET_ENT_PAIR_SERVERGAMESTATE_CLIENTGAMESTATE)
    , command(command)
{
}

ServerGameState::~ServerGameState()
{
}

void ServerGameState::playerJoined(int numPlayers)
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = MSG_T_PLAYER_CONNECTED;
    msg.data = (void*) &numPlayers;
    msg.len = sizeof(numPlayers);

    update(msg);
}

void ServerGameState::playerLeft(int numPlayers)
{
    printf("PLAYER LEFT\r\n");

    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = MSG_T_PLAYER_DISCONNECTED;
    msg.data = (void*) &numPlayers;
    msg.len = sizeof(numPlayers);

    update(msg);
}

void ServerGameState::startLobbyCountdown(int remainingTime)
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = MSG_T_LOBBY_COUNTDOWN_START;
    msg.data = (void*) &(remainingTime);
    msg.len = sizeof(remainingTime);

    update(msg);
}

void ServerGameState::stopLobbyCountdown(int remainingTime)
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = MSG_T_LOBBY_COUNTDOWN_STOP;
    msg.data = (void*) &(remainingTime);
    msg.len = sizeof(remainingTime);

    update(msg);
}

void ServerGameState::goToLobby()
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = MSG_T_SERVERGAMESTATE_CLIENTGAMESTATE_START_LOBBY_SCENE;
    msg.data = (void*) "GO TO LOBBY";
    msg.len = strlen((char*)msg.data);

    update(msg);
}

void ServerGameState::goToGame(bool inProgress)
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = MSG_T_SERVERGAMESTATE_CLIENTGAMESTATE_START_GAME_SCENE;
    msg.data = (void*) "GO TO GAME SCENE";
    msg.len = strlen((char*)msg.data);

    update(msg);
}

void ServerGameState::onUnregister(Networking::Session *session,
                                   Networking::Message message)
{
    command->playerLeft(session);
}

void ServerGameState::onUpdate(Networking::Message message)
{
}
