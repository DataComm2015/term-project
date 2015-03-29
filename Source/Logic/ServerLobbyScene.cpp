#include "ServerLobbyScene.h"
#include <iostream>

#include "NetworkEntityPairs.h"
#include "ServerCommand.h"
#include "Entities/PlayerEntity.h"
#include "Entities/ServerGameState.h"

#define SERVER_INITIAL_TIMER_VALUE 5
#define SERVER_LOBBY_MIN_REQUIRED_PLAYERS 2

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

ServerLobbyScene::ServerLobbyScene(ServerCommand *command)
    : command(command)
{
    timerRunning = false;
    timer = SERVER_INITIAL_TIMER_VALUE;
}

ServerLobbyScene::~ServerLobbyScene()
{
    //
}

void ServerLobbyScene::update(sf::Time time)
{
	if (timerRunning)
	{
	    printf("TIMER: %d\r\n", time.asSeconds());
	    timer -= time.asSeconds();
	    
	    if (timer <= 0)
	    {
	        command->goToGame();
	    }
	}
}

/*
 * Server Doesn't Need SF Events
 */
void ServerLobbyScene::processEvents(sf::Event& e){}

/*
 * Server Doesn't Draw Anything
 */
void ServerLobbyScene::draw(){}

/*
 * Add a Player to the Lobby
 */
void ServerLobbyScene::addPlayer(Session *session, PlayerEntity *entity)
{
    players[session] = entity;
    
    if (players.size() >= SERVER_LOBBY_MIN_REQUIRED_PLAYERS)
    {
        startTimer();
    }
}

/*
 * Remove a player from the lobby
 */
void ServerLobbyScene::removePlayer(Session *session)
{
    players.erase(players.find(session));
    
    if (players.size() < SERVER_LOBBY_MIN_REQUIRED_PLAYERS)
    {
        stopTimer();
    }
}

std::map<Session*, PlayerEntity*> ServerLobbyScene::getPlayers()
{
    return players;
}

void ServerLobbyScene::enterScene()
{
    timerRunning = false;
    timer = SERVER_INITIAL_TIMER_VALUE;
    
    if (players.size() >= SERVER_LOBBY_MIN_REQUIRED_PLAYERS)
    {
        startTimer();
    }
}

void ServerLobbyScene::startTimer()
{
    timerRunning = true;
    command->getGameState()->startLobbyCountdown(timer);
}

void ServerLobbyScene::stopTimer()
{
    timerRunning = false;
    command->getGameState()->stopLobbyCountdown(timer);
}
