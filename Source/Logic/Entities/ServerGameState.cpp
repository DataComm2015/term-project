#include "ServerGameState.h"

#include <cstring>
#include "../ServerCommand.h"
#include "../NetworkEntityPairs.h"
#include "../../Network/Session.h"
#include "PlayerEntity.h"

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

void ServerGameState::playerJoined(Session *session, PlayerEntity *player)
{
    players[session] = player;
    int playerCount = players.size();

    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = MSG_T_PLAYER_CONNECTED;
    msg.data = (void*) &playerCount;
    msg.len = sizeof(int);

    update(msg);
}

void ServerGameState::playerLeft(Session *session)
{
    printf("PLAYER LEFT\r\n");
    int playerCount;
    
    Message msg;
    memset(&msg,0,sizeof(msg));
    players[session]->unregisterSession(session, msg);

    std::map<Session*,PlayerEntity*>::iterator itr = players.find(session);
    if (itr != players.end())
    {
        players.erase(itr);
    }

    playerCount = players.size();

    msg.type = MSG_T_PLAYER_DISCONNECTED;
    msg.data = (void*) &playerCount;
    msg.len = sizeof(int);

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

std::map<Session*, PlayerEntity*> ServerGameState::getPlayers()
{
    return players;
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
}

void ServerGameState::onUpdate(Networking::Message message)
{
}