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

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::ServerGameState(S
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel, Eric Tsang
--
-- INTERFACE:       ServerGameState::ServerGameState(ServerCommand *command)
--                  command - pointer to the {ServerCommand} singleton.
--
-- RETURNS:         void
--
-- NOTES:           constructor for the {ServerGameState} class.
------------------------------------------------------------------------------*/
ServerGameState::ServerGameState(ServerCommand *command)
    : NetworkEntity((int)NetworkEntityPair::SERVERGAMESTATE_CLIENTGAMESTATE)
    , command(command)
{
    srand(time(NULL));
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::~ServerGameState()
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       ServerGameState::~ServerGameState()
--
-- RETURNS:         void
--
-- NOTES:           destructor for the {ServerGameState} class.
------------------------------------------------------------------------------*/
ServerGameState::~ServerGameState()
{
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::playerJoined(S
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       void ServerGameState::playerJoined(Session *session,
--                      PlayerEntity *player)
--                  session - pointer to the session which identifies the
--                            connection with the player.
--                  player  - pointer to the player entity, which holds
--                            game-related information about the player
--
-- RETURNS:         void
--
-- NOTES:           indicates to the {ServerGameState} that a new player has
--                  joined.
--
--                  the player is added to a list of players, and the game state
--                  is updated.
--
--                  a message is also sent out to all clients, informing them
--                  that a new player has joined.
------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::playerLeft
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       void ServerGameState::playerLeft(Session *session)
--                  session - pointer to the session object that's related to
--                            the player.
--
-- RETURNS:         void
--
-- NOTES:           indicates to the {ServerGameState} that a player has left.
--
--                  the player is removed from the list of players, and the game
--                  state is updated.
--
--                  a message is also sent out to all clients, informing them
--                  that a player has joined.
------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::startLobbyCountdown
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       void ServerGameState::startLobbyCountdown(int remainingTime)
--                  remainingTime -
--
-- RETURNS:         void
--
-- NOTES:           sends a message to the clients, indicating to them to start
--                  their lobby countdown.
------------------------------------------------------------------------------*/
void ServerGameState::startLobbyCountdown(int remainingTime)
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = (int)ServerGameStateClientGameStateMsgType::LOBBY_COUNTDOWN_START;
    msg.data = (void*) &(remainingTime);
    msg.len = sizeof(remainingTime);

    update(msg);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::stopLobbyCountdown
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       void ServerGameState::stopLobbyCountdown(int remainingTime)
--                  remainingTime -
--
-- RETURNS:         void
--
-- NOTES:           sends a message to the clients, indicating to them to stop
--                  their lobby countdown.
------------------------------------------------------------------------------*/
void ServerGameState::stopLobbyCountdown(int remainingTime)
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = (int)ServerGameStateClientGameStateMsgType::LOBBY_COUNTDOWN_STOP;
    msg.data = (void*) &(remainingTime);
    msg.len = sizeof(remainingTime);

    update(msg);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        :map<Session
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       std::map<Session*, PlayerEntity*> ServerGameState::getPlayers()
--
-- RETURNS:         void
--
-- NOTES:           returns a copy of the map of players that are currently
--                  connected to the server.
------------------------------------------------------------------------------*/
std::map<Session*, PlayerEntity*> ServerGameState::getPlayers()
{
    return players;
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::goToScoreboard
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Manuel Gonzales
--
-- PROGRAMMER:      Manuel Gonzales
--
-- INTERFACE:       void ServerGameState::goToScoreboard()
--
-- RETURNS:         void
--
-- NOTES:           tells the clients that they should go to the scoreboard
--                  scene.
------------------------------------------------------------------------------*/
void ServerGameState::goToScoreboard()
{

    Player player_stats[12];
    auto players = getPlayers();
    int i = 0;

    for(i = 0; i < 12; i++)
    {
        strcpy(player_stats[i].name, "");
        player_stats[i].type = -1;
        player_stats[i].score = 0;
    }

    i = 0;

    for(auto entry = players.begin(); entry != players.end(); ++entry)
    {
        PlayerEntity* playerEntity = entry->second;
        strcpy(player_stats[i].name, playerEntity->getNickname());
        fprintf(stdout, "SERVER NICKNAME: %s\n", playerEntity->getNickname());
        fflush(stdout);
        player_stats[i].type = (int) playerEntity->getMode();
        player_stats[i].score = playerEntity->getPoints();
        i++;
    }

    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = (int)ServerGameStateClientGameStateMsgType::START_SCORE_SCENE;
    msg.data = (void*) player_stats;
    msg.len = sizeof(Player) * 12;

    update(msg);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::goToLobby
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       void ServerGameState::goToLobby()
--
-- RETURNS:         void
--
-- NOTES:           tells the clients that they should go to the lobby scene.
------------------------------------------------------------------------------*/
void ServerGameState::goToLobby()
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = (int)ServerGameStateClientGameStateMsgType::START_LOBBY_SCENE;
    msg.data = (void*) "GO TO LOBBY";
    msg.len = strlen((char*)msg.data);

    update(msg);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::prepareForGameState
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       void ServerGameState::prepareForGameState()
--
-- RETURNS:         void
--
-- NOTES:           indicates to the client that they should prepare for the
--                  start of the game. when clients receive this message, they
--                  should send the server their "loadout" information.
--
--                  the server will wait for everyone's loadout information
--                  before starting the game.
------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::notifyReadyForGame
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       void ServerGameState::notifyReadyForGame()
--
-- RETURNS:         void
--
-- NOTES:           invoked when we recieve the loadout from one of the clients
--                  after sending out the "prepare for game start" message.
--
--                  it detects if everyone has sent the server their loadout or
--                  not yet, and when the last player submits their loadout to
--                  the server, then the server sends the gotogamescene message
--                  to the clients, and the game begins.
------------------------------------------------------------------------------*/
void ServerGameState::notifyReadyForGame()
{
    playersWaitingToLaunch--;

    if (playersWaitingToLaunch <= 0)
    {
        command->goToGame();
        goToGame(command->getGameScene()->getWorldSeed());
    }
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::goToGame
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       void ServerGameState::goToGame(int worldSeed)
--                  worldSeed -
--
-- RETURNS:         void
--
-- NOTES:           indicates to all clients to go to the game scene.
------------------------------------------------------------------------------*/
void ServerGameState::goToGame(int worldSeed)
{
    Message msg;
    memset(&msg,0,sizeof(msg));
    msg.type = (int)ServerGameStateClientGameStateMsgType::START_GAME_SCENE;
    msg.data = (void*) &worldSeed;
    msg.len = sizeof(worldSeed);

    update(msg);
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::assignPlayerModes
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       void ServerGameState::assignPlayerModes()
--
-- RETURNS:         void
--
-- NOTES:           assigns players to their game roles. picks randomly if
--                  needed.
------------------------------------------------------------------------------*/
void ServerGameState::assignPlayerModes()
{
    int vesselsRemaining = NUM_VESSELS;
    int count = 0;
    int randNum;

    /* Assign each player a type (VESSEL OR DEITY) */
    std::map<Session*, PlayerEntity*>::iterator itr = players.begin();
    while (itr != players.end())
    {
        PLAYER_INFO info;
        // If there are still vessels left to place, check if player should be
        // vessel
        if (vesselsRemaining > 0)
        {
            // If there are only enough players left for vessels, make them
            // vessels.
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

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::registerWithAllPlayers
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       void ServerGameState::registerWithAllPlayers(
--                      Networking::NetworkEntity *entity, Message *msg)
--
-- RETURNS:         void
--
-- NOTES:           helper function used to register the passed network entity
--                  with all players, and send them a message along with it.
------------------------------------------------------------------------------*/
void ServerGameState::registerWithAllPlayers(Networking::NetworkEntity *entity, Message *msg)
{
    std::map<Session*, PlayerEntity*>::iterator itr = players.begin();
    while (itr != players.end())
    {
        entity->registerSession(itr->first, *msg);
        itr++;
    }
}

/*------------------------------------------------------------------------------
-- FUNCTION:        ServerGameState::unregisterFromAllPlayers
--
-- DATE:            March 28, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Calvin Rempel
--
-- PROGRAMMER:      Calvin Rempel
--
-- INTERFACE:       void ServerGameState::unregisterFromAllPlayers(
--                      Networking::NetworkEntity *entity)
--                  entity -
--
-- RETURNS:         void
--
-- NOTES:           helper function used to unregister the passed network entity
--                  from all players.
------------------------------------------------------------------------------*/
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
/**
 * @brief ServerGameState::update
 *  This overrides NetworkEntity on update so that if a player joins after,
 *  they can be send to a fake lobby, but are then picked up by the game the
 *  next round.
 *
 * @param message
 * message to send
 * @author  Jeff Bayntun
 * @designer Jeff Bayntun
 */
/*----------------------------------------------------------------------------------------------
-- FUNCTION:        onConnect
--
-- DATE:            February 27, 2015
--
-- REVISIONS:       (Date and Description)
--
-- DESIGNER:        Jeff Bayntun
--
-- PROGRAMMER:      Jeff Bayntun
--
-- INTERFACE:       void ServerGameState::update( Message message )

-- RETURNS:         void
--
-- NOTES:          sends a message to a specific session that they should go to the
                    fake lobby if a game is already in progress.  A pointer to the
                    sesssion MUST be passed as the message.data
-----------------------------------------------------------------------------------------------*/
void ServerGameState::update( Message message )
{
    if(message.type == (int)ServerGameStateClientGameStateMsgType::FAKE_LOBBY)
    {
        Session* session = (Session*) message.data;
        std::set<Session*> mySet;
        mySet.insert(session);
        mux->update(id, mySet, message);
        return;
    }
    NetworkEntity::update(message);

}
