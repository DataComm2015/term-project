#ifndef SERVER_LOBBY_SCENE_H_
#define SERVER_LOBBY_SCENE_H_

#include <vector>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include "../Engine/Scene.h"
#include "../Environment/GameMap.h"
#include "../AppWindow.h"
#include "../Engine/TextureManager.h"
#include "../Multimedia/graphics/Renderer.h"

/*
*	This is the In-game Scene where all round-events occur.
*/
class ServerLobbyScene : public Scene
{
	public:
		ServerLobbyScene();
		virtual void update(sf::Time);
		virtual void processEvents(sf::Event&);
		virtual void draw();
		~ServerLobbyScene();

	private:

    	sf::View viewMain;
};

#endif
