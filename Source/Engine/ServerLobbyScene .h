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
#include "../Multimedia/gui/Button.h"
#include "../graphics/object/BGO.h"

using GUI::Button;

/*
*	This is the Lobby scene.
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

        BGO * parent;

        Button * vesselOneBtn;
        Button * vesselTwoBtn;

        Button * aspectOneBtn;
        Button * aspectTwoBtn;
        Button * aspectThreeBtn;

        Button * readyBtn;
};

#endif
