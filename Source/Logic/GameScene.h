#ifndef GAME_SCENE_H_
#define GAME_SCENE_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include "../Engine/Scene.h"
#include "../Engine/Map.h"
#include "../AppWindow.h"
#include <cstdio>


/*
* Testing Game Scene
*/
class GameScene : public Scene
{
	public:
		GameScene();
		virtual void update(sf::Time);
		virtual void processEvents(sf::Event&);
		virtual void draw();
		~GameScene();
	private:
		Marx::Map *cMap;
		GameMap *gMap;
};

#endif