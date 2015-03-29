#include "ServerGameState.h"

#include <cstring>
#include "../NetworkEntityPairs.h"

using Networking::NetworkEntity;
using Networking::Session;
using Networking::Message;

ServerGameState::ServerGameState(ServerCommand *command)
    : NetworkEntity(100), command(command)
{
}

ServerGameState::~ServerGameState()
{
}

void ServerGameState::playerJoined()
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = MSG_T_PLAYER_CONNECTED;
    
    update(msg);
}

void ServerGameState::playerLeft()
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = MSG_T_PLAYER_DISCONNECTED;
    
    update(msg);
}

void ServerGameState::startLobbyCountdown(int remainingTime)
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = MSG_T_LOBBY_COUNTDOWN_STOP;
    msg.data = &(remainingTime);
    msg.len = sizeof(remainingTime);
    
    update(msg);
}

void ServerGameState::stopLobbyCountdown(int remainingTime)
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = MSG_T_LOBBY_COUNTDOWN_STOP;
    msg.data = &(remainingTime);
    msg.len = sizeof(remainingTime);
    
    update(msg);
}

void ServerGameState::goToLobby()
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = 100; // GO TO LOBBY SCENE
    msg.data = (void*) "HELLO WORLD";
    msg.len = strlen((char*)msg.data);
    
    update(msg);
}

void ServerGameState::goToGame()
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = 0; // GO TO GAME SCENE
    
    update(msg);
}

void ServerGameState::onUnregister(Networking::Session *session,
                                   Networking::Message message)                                 
{
}

void ServerGameState::onUpdate(Networking::Message message)
{
}
