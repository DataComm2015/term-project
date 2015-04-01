#include "ServerGameState.h"

#include <cstring>
#include <ctime>
#include <cstdlib>

#include "../ServerGameScene.h"
#include "../../GameSettings.h"
#include "../ServerCommand.h"
#include "../NetworkEntityPairs.h"
#include "../../Network/Session.h"
#include "PlayerEntity.h"

using Networking::NetworkEntity;
using Networking::Session;
using Networking::Message;

ServerGameState::ServerGameState(ServerCommand *command)
    : NetworkEntity((int)NetworkEntityPair::SERVERGAMESTATE_CLIENTGAMESTATE)
    , command(command)
{
    srand(time(NULL));
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
    msg.type = (int)ServerGameStateClientGameStateMsgType::PLAYER_CONNECTED;
    msg.data = (void*) &playerCount;
    msg.len = sizeof(int);

    update(msg);
}

void ServerGameState::playerLeft(Session *session)
{
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
    playersWaitingToLaunch--;

    msg.type = (int)ServerGameStateClientGameStateMsgType::PLAYER_DISCONNECTED;
    msg.data = (void*) &playerCount;
    msg.len = sizeof(int);

    update(msg);
}

void ServerGameState::startLobbyCountdown(int remainingTime)
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = (int)ServerGameStateClientGameStateMsgType::LOBBY_COUNTDOWN_START;
    msg.data = (void*) &(remainingTime);
    msg.len = sizeof(remainingTime);

    update(msg);
}

void ServerGameState::stopLobbyCountdown(int remainingTime)
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = (int)ServerGameStateClientGameStateMsgType::LOBBY_COUNTDOWN_STOP;
    msg.data = (void*) &(remainingTime);
    msg.len = sizeof(remainingTime);

    update(msg);
}

std::map<Session*, PlayerEntity*> ServerGameState::getPlayers()
{
    return players;
}

void ServerGameState::goToScoreboard()
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = (int)ServerGameStateClientGameStateMsgType::START_SCORE_SCENE;
    msg.data = (void*) "GO TO SCORE";
    msg.len = strlen((char*)msg.data);

    update(msg);
}

void ServerGameState::goToLobby()
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = (int)ServerGameStateClientGameStateMsgType::START_LOBBY_SCENE;
    msg.data = (void*) "GO TO LOBBY";
    msg.len = strlen((char*)msg.data);

    update(msg);
}

void ServerGameState::prepareForGameState()
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = (int)ServerGameStateClientGameStateMsgType::READY_FOR_GAME;
    msg.data = (void*) "PREPARE FOR GAME START";
    msg.len = strlen((char*)msg.data);

    assignPlayerModes();
    playersWaitingToLaunch = players.size();

    update(msg);
}

void ServerGameState::notifyReadyForGame()
{
    playersWaitingToLaunch--;

    if (playersWaitingToLaunch <= 0)
    {
        command->goToGame();
        goToGame(command->getGameScene()->getWorldSeed());
    }
}

void ServerGameState::goToGame(int worldSeed)
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = (int)ServerGameStateClientGameStateMsgType::START_GAME_SCENE;
    msg.data = (void*) &worldSeed;
    msg.len = sizeof(worldSeed);

    update(msg);
}

void ServerGameState::onUnregister(Networking::Session *session,
                                   Networking::Message message)
{
}

void ServerGameState::onUpdate(Networking::Message message)
{
}

void ServerGameState::assignPlayerModes()
{
    int vesselsRemaining = NUM_VESSELS;
    int count = 0;
    int randNum;

    /* Assign each player a type (VESSEL OR DEITY) */
    std::map<Session*, PlayerEntity*>::iterator itr = players.begin();
    while (itr != players.end())
    {
        // If there are still vessels left to place, check if player should be vessel
        if (vesselsRemaining > 0)
        {
            // If there are only enough players left for vessels, make them vessels.
            if (players.size() - count <= NUM_VESSELS)
            {
                itr->second->setMode(PLAYER_MODE::VESSEL);
                vesselsRemaining--;
            }
            // If player could be either a vessel or a deity, choose randomly
            else
            {
                randNum = rand() % players.size();
                if (randNum < NUM_VESSELS )
                {
                    itr->second->setMode(PLAYER_MODE::VESSEL);
                    vesselsRemaining--;
                }
                else
                {
                    itr->second->setMode(PLAYER_MODE::DEITY);
                }
            }
        }
        // If all vessels have been chosen, remaining players are deities
        else
        {
            itr->second->setMode(PLAYER_MODE::DEITY);
        }

        count++;
        itr++;
    }
}

void ServerGameState::registerWithAllPlayers(Networking::NetworkEntity *entity, Message *msg)
{
    std::map<Session*, PlayerEntity*>::iterator itr = players.begin();
    while (itr != players.end())
    {
        entity->registerSession(itr->first, *msg);
        itr++;
    }
}

void ServerGameState::unregisterFromAllPlayers(Networking::NetworkEntity *entity)
{
    Message msg;
    memset(&msg, 0, sizeof(msg));

    std::map<Session*, PlayerEntity*>::iterator itr = players.begin();
    while (itr != players.end())
    {
        entity->unregisterSession(itr->first, msg);
        itr++;
    }
}






