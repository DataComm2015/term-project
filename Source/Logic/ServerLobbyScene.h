#ifndef SERVER_LOBBY_SCENE_H_
#define SERVER_LOBBY_SCENE_H_

#include <map>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "../Network/Session.h"
#include "../Engine/Scene.h"

class PlayerEntity;
class ServerCommand;

using Marx::Scene;
using Networking::Session;

/*
*	This is the Lobby scene.
*/
class ServerLobbyScene : public Scene
{
	public:
		ServerLobbyScene(ServerCommand *command);
		~ServerLobbyScene();
		virtual void update(sf::Time);
		virtual void processEvents(sf::Event&);
		virtual void draw();
        void onclick();
        
        void enterScene();
        void addPlayer(Session *session, PlayerEntity*);
        void removePlayer(Session *session);
        std::map<Session*, PlayerEntity*> getPlayers();

	private:
	    ServerCommand *command;
    	sf::View viewMain;
    	float timer;
    	bool timerRunning;
    	std::map<Session*, PlayerEntity*> players;
    	
    	void startTimer();
    	void stopTimer();
};

#endif
