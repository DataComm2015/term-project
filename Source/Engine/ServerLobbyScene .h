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

#define BTN_SIZE 200

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
        void onclick();

	private:

    	sf::View viewMain;
        Renderer renderer;

        SGO background;
        id_resource backgroundImg;

        GUI::Button * vesselOneBtn;
        GUI::Button * vesselTwoBtn;

        GUI::Button * aspectOneBtn;
        GUI::Button * aspectTwoBtn;
        GUI::Button * aspectThreeBtn;
        
        GUI::Button * readyBtn;

        id_resource vesselOneImg;
        id_resource vesselTwoImg;

        id_resource aspectOneImg;
        id_resource aspectTwoImg;
        id_resource aspectThreeImg;

        id_resource readyImg;
};

#endif
