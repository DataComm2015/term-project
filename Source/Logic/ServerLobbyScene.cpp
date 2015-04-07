#include "ServerLobbyScene.h"
#include <iostream>

#include "../GameSettings.h"
#include "NetworkEntityPairs.h"
#include "ServerCommand.h"
#include "Entities/ServerGameState.h"

using std::cout;
using std::cerr;
using std::endl;
using namespace Marx;

ServerLobbyScene::ServerLobbyScene(ServerCommand *command)
    : command(command)
{
    playerCount = 0;
    timerRunning = false;
    waitingToStart = false;
    timer = SERVER_INITIAL_TIMER_VALUE;
}

ServerLobbyScene::~ServerLobbyScene()
{
    //
}

void ServerLobbyScene::update(sf::Time time)
{
    // Networking::handleSessionMessages();
	if (timerRunning && !waitingToStart)
	{
	    timer -= time.asSeconds();

	    if (timer <= 0)
	    {
            waitingToStart = true;
	        command->prepareForGameState();
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

    if (playerCount >= MIN_REQUIRED_PLAYERS)
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

    if (playerCount < MIN_REQUIRED_PLAYERS)
    {
        stopTimer();
    }
}

void ServerLobbyScene::enterScene()
{
    waitingToStart = false;
    timerRunning = false;
    timer = SERVER_INITIAL_TIMER_VALUE;

    if (playerCount >= MIN_REQUIRED_PLAYERS)
    {
        startTimer();
    }
}

void ServerLobbyScene::leaveScene()
{
    playerCount = 0;
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
