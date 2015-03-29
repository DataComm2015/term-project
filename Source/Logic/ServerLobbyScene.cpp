#include "ServerLobbyScene.h"
#include <iostream>

#include "NetworkEntityPairs.h"
#include "ServerCommand.h"
#include "Entities/ServerGameState.h"

#define SERVER_INITIAL_TIMER_VALUE 20
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
void ServerLobbyScene::addPlayer()
{
    playerCount++;
    
    if (playerCount >= SERVER_LOBBY_MIN_REQUIRED_PLAYERS)
    {
        startTimer();
    }
}

/*
 * Remove a player from the lobby
 */
void ServerLobbyScene::removePlayer()
{
    playerCount--;

    if (playerCount < SERVER_LOBBY_MIN_REQUIRED_PLAYERS)
    {
        stopTimer();
    }
}

void ServerLobbyScene::enterScene()
{
    timerRunning = false;
    timer = SERVER_INITIAL_TIMER_VALUE;
    
    if (playerCount >= SERVER_LOBBY_MIN_REQUIRED_PLAYERS)
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